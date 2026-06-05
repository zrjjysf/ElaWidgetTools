#include "AlphaUiService.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QProcess>

AlphaUiService::AlphaUiService(QObject* parent)
    : QObject(parent)
{
}

AlphaUiService::~AlphaUiService()
{
    if (_process)
    {
        _process->kill();
        _process->deleteLater();
    }
}

void AlphaUiService::fetchAlphaList(const AlphaListRequest& request)
{
    QStringList arguments{mainScriptPath(), "alpha-list", "--sort", request.sort, "--limit", QString::number(request.limit)};
    if (request.pointsMultiplier != "any")
    {
        arguments << "--points-multiplier" << request.pointsMultiplier;
    }
    if (!request.chain.trimmed().isEmpty())
    {
        arguments << "--chain" << request.chain.trimmed();
    }
    if (request.includeInactive)
    {
        arguments << "--include-inactive";
    }
    startProcess(arguments, RequestKind::AlphaList);
}

void AlphaUiService::fetchAlphaDetail(const QString& query)
{
    const QString trimmedQuery = query.trimmed();
    if (trimmedQuery.isEmpty())
    {
        emit requestFailed("symbol 为空，无法加载详情。");
        return;
    }
    startProcess(QStringList{mainScriptPath(), "alpha-check", trimmedQuery}, RequestKind::AlphaDetail);
}

bool AlphaUiService::isBusy() const
{
    return _process != nullptr;
}

void AlphaUiService::startProcess(const QStringList& arguments, RequestKind kind)
{
    if (_process)
    {
        _process->kill();
        _process->deleteLater();
        _process = nullptr;
    }

    _requestKind = kind;
    _outputPath = createOutputPath(kind == RequestKind::AlphaList ? "alpha-list" : "alpha-detail");

    QStringList fullArguments = arguments;
    fullArguments << "--json-out" << _outputPath;

    _process = new QProcess(this);
    _process->setProgram(pythonExecutable());
    _process->setArguments(fullArguments);
    _process->setWorkingDirectory(QDir::cleanPath(QCoreApplication::applicationDirPath() + "/../../.."));

    connect(_process, qOverload<int, QProcess::ExitStatus>(&QProcess::finished), this, &AlphaUiService::finishCurrentProcess);
    connect(_process, &QProcess::errorOccurred, this, [this](QProcess::ProcessError) {
        const QString errorText = _process ? _process->errorString() : QString("unknown process error");
        if (_process)
        {
            _process->deleteLater();
            _process = nullptr;
        }
        _requestKind = RequestKind::None;
        emit busyChanged(false);
        emit requestFailed(QString("CLI 启动失败: %1").arg(errorText));
    });

    emit busyChanged(true);
    _process->start();
}

QString AlphaUiService::pythonExecutable() const
{
    const QString root = QDir::cleanPath(QCoreApplication::applicationDirPath() + "/../../..");
    const QString venvPython = root + "/.venv/bin/python";
    if (QFile::exists(venvPython))
    {
        return venvPython;
    }
    return "python3";
}

QString AlphaUiService::mainScriptPath() const
{
    return QDir::cleanPath(QCoreApplication::applicationDirPath() + "/../../../src/main.py");
}

QString AlphaUiService::createOutputPath(const QString& prefix) const
{
    const QString tempDir = QDir::tempPath() + "/binance-shell-ui";
    QDir().mkpath(tempDir);
    return QString("%1/%2-%3.json").arg(tempDir, prefix, QString::number(QDateTime::currentMSecsSinceEpoch()));
}

void AlphaUiService::finishCurrentProcess(int exitCode, QProcess::ExitStatus exitStatus)
{
    const QByteArray stdErr = _process ? _process->readAllStandardError() : QByteArray();
    const QByteArray stdOut = _process ? _process->readAllStandardOutput() : QByteArray();
    if (_process)
    {
        _process->deleteLater();
        _process = nullptr;
    }

    const RequestKind finishedKind = _requestKind;
    _requestKind = RequestKind::None;
    emit busyChanged(false);

    if (exitStatus != QProcess::NormalExit || exitCode != 0)
    {
        QString message = QString::fromUtf8(stdErr).trimmed();
        if (message.isEmpty())
        {
            message = QString::fromUtf8(stdOut).trimmed();
        }
        if (message.isEmpty())
        {
            message = QString("CLI 返回非零状态: %1").arg(exitCode);
        }
        emit requestFailed(message);
        return;
    }

    QFile file(_outputPath);
    if (!file.open(QIODevice::ReadOnly))
    {
        emit requestFailed(QString("无法读取 JSON 输出: %1").arg(_outputPath));
        return;
    }
    const QByteArray payload = file.readAll();
    file.remove();

    if (finishedKind == RequestKind::AlphaList)
    {
        emit alphaListLoaded(payload);
        return;
    }
    if (finishedKind == RequestKind::AlphaDetail)
    {
        emit alphaDetailLoaded(payload);
    }
}

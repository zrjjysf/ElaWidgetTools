#ifndef ALPHAUISERVICE_H
#define ALPHAUISERVICE_H

#include <QObject>
#include <QProcess>

struct AlphaListRequest
{
    QString sort;
    QString pointsMultiplier;
    QString chain;
    bool includeInactive{false};
    int limit{200};
};

class AlphaUiService : public QObject
{
    Q_OBJECT

public:
    explicit AlphaUiService(QObject* parent = nullptr);
    ~AlphaUiService() override;

    void fetchAlphaList(const AlphaListRequest& request);
    void fetchAlphaDetail(const QString& query);
    bool isBusy() const;

Q_SIGNALS:
    void alphaListLoaded(const QByteArray& payload);
    void alphaDetailLoaded(const QByteArray& payload);
    void requestFailed(const QString& message);
    void busyChanged(bool busy);

private:
    enum class RequestKind
    {
        None,
        AlphaList,
        AlphaDetail,
    };

    void startProcess(const QStringList& arguments, RequestKind kind);
    QString pythonExecutable() const;
    QString mainScriptPath() const;
    QString createOutputPath(const QString& prefix) const;
    void finishCurrentProcess(int exitCode, QProcess::ExitStatus exitStatus);

    QProcess* _process{nullptr};
    RequestKind _requestKind{RequestKind::None};
    QString _outputPath;
};

#endif // ALPHAUISERVICE_H

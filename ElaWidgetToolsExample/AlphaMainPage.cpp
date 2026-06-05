#include "AlphaMainPage.h"

#include <QHeaderView>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPlainTextEdit>
#include <QStandardItemModel>
#include <QVBoxLayout>

#include "ElaComboBox.h"
#include "ElaLineEdit.h"
#include "ElaMessageBar.h"
#include "ElaPushButton.h"
#include "ElaTableView.h"
#include "ElaText.h"
#include "ElaToggleSwitch.h"

namespace
{
QString jsonToPrettyText(const QJsonValue& value)
{
    if (value.isObject())
    {
        return QString::fromUtf8(QJsonDocument(value.toObject()).toJson(QJsonDocument::Indented));
    }
    if (value.isArray())
    {
        return QString::fromUtf8(QJsonDocument(value.toArray()).toJson(QJsonDocument::Indented));
    }
    if (value.isString())
    {
        return value.toString();
    }
    if (value.isDouble())
    {
        return QString::number(value.toDouble());
    }
    if (value.isBool())
    {
        return value.toBool() ? "true" : "false";
    }
    return "null";
}
}

AlphaMainPage::AlphaMainPage(QWidget* parent)
    : T_BasePage(parent)
    , _service(new AlphaUiService(this))
{
    setWindowTitle("Alpha Monitor");
    createCustomWidget("实时查看 Binance Alpha 列表，手动刷新、筛选、排序，并查看单个 token 详情。");
    buildUi();
    connectSignals();
    reloadAlphaList();
}

AlphaMainPage::~AlphaMainPage()
{
}

void AlphaMainPage::buildUi()
{
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* rootLayout = new QVBoxLayout(centralWidget);
    rootLayout->setContentsMargins(0, 0, 12, 0);
    rootLayout->setSpacing(12);

    QWidget* filterBar = new QWidget(this);
    QHBoxLayout* filterLayout = new QHBoxLayout(filterBar);
    filterLayout->setContentsMargins(0, 0, 0, 0);
    filterLayout->setSpacing(10);

    ElaText* pointsLabel = new ElaText("倍率", this);
    _pointsFilter = new ElaComboBox(this);
    _pointsFilter->addItem("全部", "any");
    _pointsFilter->addItem("4x", "4");
    _pointsFilter->addItem("2x", "2");
    _pointsFilter->addItem("无倍率", "none");

    ElaText* sortLabel = new ElaText("排序", this);
    _sortFilter = new ElaComboBox(this);
    _sortFilter->addItem("24h Volume", "volume");
    _sortFilter->addItem("Liquidity", "liquidity");
    _sortFilter->addItem("Market Cap", "market_cap");
    _sortFilter->addItem("Listing Time", "listing_time");

    ElaText* chainLabel = new ElaText("Chain", this);
    _chainFilter = new ElaLineEdit(this);
    _chainFilter->setPlaceholderText("BSC / Solana / Base");
    _chainFilter->setFixedWidth(180);

    ElaText* inactiveLabel = new ElaText("包含非 active", this);
    _includeInactive = new ElaToggleSwitch(this);

    _refreshButton = new ElaPushButton("刷新列表", this);
    _refreshButton->setFixedHeight(36);
    _refreshButton->setMinimumWidth(110);

    _summaryText = new ElaText("尚未加载数据", this);
    _statusText = new ElaText("空闲", this);

    filterLayout->addWidget(pointsLabel);
    filterLayout->addWidget(_pointsFilter);
    filterLayout->addWidget(sortLabel);
    filterLayout->addWidget(_sortFilter);
    filterLayout->addWidget(chainLabel);
    filterLayout->addWidget(_chainFilter);
    filterLayout->addWidget(inactiveLabel);
    filterLayout->addWidget(_includeInactive);
    filterLayout->addStretch();
    filterLayout->addWidget(_statusText);
    filterLayout->addWidget(_refreshButton);

    _tableView = new ElaTableView(this);
    _tableModel = new QStandardItemModel(this);
    _tableModel->setHorizontalHeaderLabels(QStringList{"Symbol", "Alpha ID", "Name", "Chain", "Pts", "Volume", "Liquidity", "Listing CEX"});
    _tableView->setModel(_tableModel);
    _tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    _tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    _tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _tableView->setAlternatingRowColors(true);
    _tableView->verticalHeader()->setHidden(true);
    _tableView->horizontalHeader()->setStretchLastSection(false);
    _tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    _tableView->setMinimumHeight(420);

    connect(_tableView, &ElaTableView::tableViewShow, this, [this]() {
        _tableView->setColumnWidth(0, 90);
        _tableView->setColumnWidth(1, 110);
        _tableView->setColumnWidth(2, 200);
        _tableView->setColumnWidth(3, 110);
        _tableView->setColumnWidth(4, 70);
        _tableView->setColumnWidth(5, 130);
        _tableView->setColumnWidth(6, 130);
        _tableView->setColumnWidth(7, 100);
    });

    _detailView = new QPlainTextEdit(this);
    _detailView->setReadOnly(true);
    _detailView->setMinimumHeight(260);
    _detailView->setPlainText("选择一行后自动加载 token 详情。");

    rootLayout->addWidget(filterBar);
    rootLayout->addWidget(_summaryText);
    rootLayout->addWidget(_tableView);
    rootLayout->addWidget(_detailView);
    addCentralWidget(centralWidget, true, false, 0);
}

void AlphaMainPage::connectSignals()
{
    connect(_refreshButton, &ElaPushButton::clicked, this, &AlphaMainPage::reloadAlphaList);
    connect(_pointsFilter, qOverload<int>(&QComboBox::currentIndexChanged), this, [this](int) { reloadAlphaList(); });
    connect(_sortFilter, qOverload<int>(&QComboBox::currentIndexChanged), this, [this](int) { reloadAlphaList(); });
    connect(_includeInactive, &ElaToggleSwitch::toggled, this, [this](bool) { reloadAlphaList(); });
    connect(_chainFilter, &QLineEdit::returnPressed, this, &AlphaMainPage::reloadAlphaList);

    connect(_tableView->selectionModel(), &QItemSelectionModel::currentRowChanged, this, [this](const QModelIndex& current) {
        if (!current.isValid())
        {
            return;
        }
        loadDetailForCurrentRow();
    });

    connect(_service, &AlphaUiService::alphaListLoaded, this, &AlphaMainPage::populateTable);
    connect(_service, &AlphaUiService::alphaDetailLoaded, this, &AlphaMainPage::populateDetail);
    connect(_service, &AlphaUiService::requestFailed, this, [this](const QString& message) {
        _statusText->setText("失败");
        ElaMessageBar::error(ElaMessageBarType::Top, "CLI Error", message, 3500, this);
    });
    connect(_service, &AlphaUiService::busyChanged, this, &AlphaMainPage::setBusy);
}

void AlphaMainPage::reloadAlphaList()
{
    AlphaListRequest request;
    request.sort = _sortFilter->currentData().toString();
    request.pointsMultiplier = _pointsFilter->currentData().toString();
    request.chain = _chainFilter->text();
    request.includeInactive = _includeInactive->getIsToggled();
    request.limit = 200;
    _detailView->setPlainText("列表刷新中...");
    _service->fetchAlphaList(request);
}

void AlphaMainPage::loadDetailForCurrentRow()
{
    const QString symbol = currentSymbol();
    if (symbol.isEmpty())
    {
        return;
    }
    _detailView->setPlainText(QString("正在加载 %1 详情...").arg(symbol));
    _service->fetchAlphaDetail(symbol);
}

void AlphaMainPage::setBusy(bool busy)
{
    _refreshButton->setEnabled(!busy);
    _pointsFilter->setEnabled(!busy);
    _sortFilter->setEnabled(!busy);
    _chainFilter->setEnabled(!busy);
    _includeInactive->setEnabled(!busy);
    _statusText->setText(busy ? "CLI 请求中" : "空闲");
}

void AlphaMainPage::updateSummary(const QList<QVariantMap>& rows)
{
    int cexCount = 0;
    int multiplierCount = 0;
    for (const QVariantMap& row : rows)
    {
        if (row.value("listing_cex").toBool())
        {
            ++cexCount;
        }
        if (row.value("points_multiplier").isValid() && !row.value("points_multiplier").isNull())
        {
            ++multiplierCount;
        }
    }
    _summaryText->setText(QString("当前 %1 个 token，listingCex=true %2 个，带积分倍率 %3 个。").arg(rows.size()).arg(cexCount).arg(multiplierCount));
}

void AlphaMainPage::populateTable(const QByteArray& payload)
{
    QString errorMessage;
    const QList<QVariantMap> rows = parseTokenArray(payload, &errorMessage);
    if (!errorMessage.isEmpty())
    {
        ElaMessageBar::error(ElaMessageBarType::Top, "Parse Error", errorMessage, 3500, this);
        return;
    }

    _rows = rows;
    _tableModel->removeRows(0, _tableModel->rowCount());
    for (const QVariantMap& row : rows)
    {
        QList<QStandardItem*> items;
        items << new QStandardItem(row.value("symbol").toString());
        items << new QStandardItem(row.value("alpha_id").toString());
        items << new QStandardItem(row.value("name").toString());
        items << new QStandardItem(row.value("chain_name").toString());
        items << new QStandardItem(formatPoints(row));
        items << new QStandardItem(formatValue(row.value("volume_24h")));
        items << new QStandardItem(formatValue(row.value("liquidity")));
        items << new QStandardItem(formatBool(row.value("listing_cex")));
        _tableModel->appendRow(items);
    }

    updateSummary(rows);
    if (_tableModel->rowCount() > 0)
    {
        _tableView->selectRow(0);
        loadDetailForCurrentRow();
    }
    else
    {
        _detailView->setPlainText("当前筛选条件下没有 token。");
    }
}

void AlphaMainPage::populateDetail(const QByteArray& payload)
{
    QString errorMessage;
    const QVariantMap detail = parseDetailObject(payload, &errorMessage);
    if (!errorMessage.isEmpty())
    {
        ElaMessageBar::error(ElaMessageBarType::Top, "Parse Error", errorMessage, 3500, this);
        return;
    }

    const QVariantMap token = detail.value("token").toMap();
    const QVariantMap capability = detail.value("capability").toMap();
    const QVariantMap ticker = detail.value("ticker").toMap();

    QStringList lines;
    lines << QString("Query: %1").arg(detail.value("query").toString());
    lines << QString("Trading Symbol: %1").arg(detail.value("trading_symbol").toString());
    lines << "";
    lines << "[Token]";
    lines << QString("symbol: %1").arg(token.value("symbol").toString());
    lines << QString("name: %1").arg(token.value("name").toString());
    lines << QString("alphaId: %1").arg(token.value("alpha_id").toString());
    lines << QString("chain: %1").arg(token.value("chain_name").toString());
    lines << QString("contract: %1").arg(token.value("contract_address").toString());
    lines << QString("listingCex: %1").arg(formatBool(token.value("listing_cex")));
    lines << QString("offline: %1").arg(formatBool(token.value("offline")));
    lines << QString("fullyDelisted: %1").arg(formatBool(token.value("fully_delisted")));
    lines << QString("points: %1").arg(formatPoints(token));
    lines << "";
    lines << "[Ticker]";
    lines << QString("lastPrice: %1").arg(formatValue(ticker.value("lastPrice")));
    lines << QString("priceChangePercent: %1").arg(formatValue(ticker.value("priceChangePercent")));
    lines << QString("volume: %1").arg(formatValue(ticker.value("volume")));
    lines << QString("quoteVolume: %1").arg(formatValue(ticker.value("quoteVolume")));
    lines << "";
    lines << "[Capability]";
    lines << QString("exists: %1").arg(formatBool(capability.value("exists")));
    lines << QString("status: %1").arg(formatValue(capability.value("status")));
    lines << QString("base/quote: %1/%2").arg(formatValue(capability.value("base_asset")), formatValue(capability.value("quote_asset")));
    lines << QString("order_types: %1").arg(capability.value("order_types").toStringList().join(", "));
    lines << "";
    lines << "[Raw Warnings]";
    for (const QVariant& warning : detail.value("warnings").toList())
    {
        lines << QString("- %1").arg(warning.toString());
    }

    if (capability.contains("filters"))
    {
        lines << "";
        lines << "[Capability Filters]";
        const QVariantList filters = capability.value("filters").toList();
        for (const QVariant& filter : filters)
        {
            lines << jsonToPrettyText(QJsonValue::fromVariant(filter));
        }
    }

    _detailView->setPlainText(lines.join("\n"));
}

QList<QVariantMap> AlphaMainPage::parseTokenArray(const QByteArray& payload, QString* errorMessage) const
{
    const QJsonDocument document = QJsonDocument::fromJson(payload);
    if (!document.isArray())
    {
        *errorMessage = "alpha-list JSON 不是数组。";
        return {};
    }

    QList<QVariantMap> rows;
    for (const QJsonValue& value : document.array())
    {
        rows.append(value.toObject().toVariantMap());
    }
    return rows;
}

QVariantMap AlphaMainPage::parseDetailObject(const QByteArray& payload, QString* errorMessage) const
{
    const QJsonDocument document = QJsonDocument::fromJson(payload);
    if (!document.isObject())
    {
        *errorMessage = "alpha-check JSON 不是对象。";
        return {};
    }
    return document.object().toVariantMap();
}

QString AlphaMainPage::formatPoints(const QVariantMap& row) const
{
    const QVariant points = row.value("points_multiplier");
    if (!points.isValid() || points.isNull())
    {
        return "-";
    }
    return QString("%1x").arg(points.toString());
}

QString AlphaMainPage::formatBool(const QVariant& value) const
{
    if (!value.isValid() || value.isNull())
    {
        return "-";
    }
    return value.toBool() ? "true" : "false";
}

QString AlphaMainPage::formatValue(const QVariant& value) const
{
    if (!value.isValid() || value.isNull())
    {
        return "-";
    }
    return value.toString();
}

QString AlphaMainPage::currentSymbol() const
{
    const QModelIndex current = _tableView->currentIndex();
    if (!current.isValid() || current.row() < 0 || current.row() >= _rows.size())
    {
        return {};
    }
    return _rows.at(current.row()).value("symbol").toString();
}

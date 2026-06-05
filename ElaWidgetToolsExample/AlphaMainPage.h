#ifndef ALPHAMAINPAGE_H
#define ALPHAMAINPAGE_H

#include "T_BasePage.h"

#include "AlphaUiService.h"

class ElaComboBox;
class ElaLineEdit;
class ElaPushButton;
class ElaTableView;
class ElaText;
class ElaToggleSwitch;
class QPlainTextEdit;
class QStandardItemModel;

class AlphaMainPage : public T_BasePage
{
public:
    explicit AlphaMainPage(QWidget* parent = nullptr);
    ~AlphaMainPage() override;

private:
    void buildUi();
    void connectSignals();
    void reloadAlphaList();
    void loadDetailForCurrentRow();
    void setBusy(bool busy);
    void updateSummary(const QList<QVariantMap>& rows);
    void populateTable(const QByteArray& payload);
    void populateDetail(const QByteArray& payload);
    QList<QVariantMap> parseTokenArray(const QByteArray& payload, QString* errorMessage) const;
    QVariantMap parseDetailObject(const QByteArray& payload, QString* errorMessage) const;
    QString formatPoints(const QVariantMap& row) const;
    QString formatBool(const QVariant& value) const;
    QString formatValue(const QVariant& value) const;
    QString currentSymbol() const;

    AlphaUiService* _service{nullptr};
    ElaComboBox* _pointsFilter{nullptr};
    ElaComboBox* _sortFilter{nullptr};
    ElaLineEdit* _chainFilter{nullptr};
    ElaToggleSwitch* _includeInactive{nullptr};
    ElaPushButton* _refreshButton{nullptr};
    ElaTableView* _tableView{nullptr};
    QStandardItemModel* _tableModel{nullptr};
    QPlainTextEdit* _detailView{nullptr};
    ElaText* _summaryText{nullptr};
    ElaText* _statusText{nullptr};
    QList<QVariantMap> _rows;
};

#endif // ALPHAMAINPAGE_H

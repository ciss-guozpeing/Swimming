#ifndef SORTFILTERPROXYMODEL_H
#define SORTFILTERPROXYMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
#include <QRegExp>


class SortFilterProxyModel: public QSortFilterProxyModel
{
    Q_OBJECT
public:
    SortFilterProxyModel(QObject* parent);
    void setRxCol0(const QString rx);
    void setRxCol2(const QString rx);
    void setRxCol3(const QString rx);
    void setRxCol4(const QString rx);
    void setRxCol6(const QString rx);
    void setRxCol7(const QString rx);
    void setRxCol8(const QString rx);
    void setRxCol9(const QString rx);
    void setRxCol10(const QString rx);
    void setRxCol11(const QString rx);
    void setRxCol19(const QString rx);
    void setRefresh(const QString rx);
    void setInvalidateFilter();
protected:
     bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const Q_DECL_OVERRIDE;
private:
    QString m_rxCol0;
    QString m_rxCol2;
    QString m_rxCol3;
    QString m_rxCol4;
    QString m_rxCol6;
    QString m_rxCol7;
    QString m_rxCol8;
    QString m_rxCol9;
    QString m_rxCol10;
    QString m_rxCol11;
    QString m_rxCol19;
    QString m_refresh;

};

#endif // SORTFILTERPROXYMODEL_H

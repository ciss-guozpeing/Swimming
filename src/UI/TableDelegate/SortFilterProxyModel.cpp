#include "SortFilterProxyModel.h"

#include <QDebug>
SortFilterProxyModel::SortFilterProxyModel(QObject* parent)
{
    Q_UNUSED(parent);
    m_rxCol0 = "";
    m_rxCol2 = "";
    m_rxCol3 = "";
    m_rxCol4 = "";
    m_rxCol6 = "";
    m_rxCol7 = "";
    m_rxCol8 = "";
    m_rxCol9 = "";
    m_rxCol10 = "";
    m_rxCol11 = "";
    m_rxCol19 = "";
}

void SortFilterProxyModel::setRxCol0(const QString rx)
{
    m_rxCol0 = rx;
}

void SortFilterProxyModel::setRxCol2(const QString rx)
{
    m_rxCol2 = rx;
}

void SortFilterProxyModel::setRxCol3(const QString rx)
{
    m_rxCol3 = rx;
}

void SortFilterProxyModel::setRxCol4(const QString rx)
{
    m_rxCol4 = rx;
}

void SortFilterProxyModel::setRxCol6(const QString rx)
{
    m_rxCol6 = rx;
}

void SortFilterProxyModel::setRxCol7(const QString rx)
{
    m_rxCol7 = rx;
}

void SortFilterProxyModel::setRxCol8(const QString rx)
{
    m_rxCol8 = rx;
}

void SortFilterProxyModel::setRxCol9(const QString rx)
{
    m_rxCol9 = rx;
}

void SortFilterProxyModel::setRxCol10(const QString rx)
{
    m_rxCol10 = rx;
}

void SortFilterProxyModel::setRxCol11(const QString rx)
{
    m_rxCol11 = rx;
}

void SortFilterProxyModel::setRxCol19(const QString rx)
{
    m_rxCol19 = rx;
}

void SortFilterProxyModel::setRefresh(const QString rx)
{
    m_refresh = rx;
}

void SortFilterProxyModel::setInvalidateFilter()
{
    invalidateFilter();
}

bool SortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex index3 = sourceModel()->index(source_row, 3, source_parent);
    QModelIndex index4 = sourceModel()->index(source_row, 4, source_parent);
    QModelIndex index6 = sourceModel()->index(source_row, 6, source_parent);
    QModelIndex index7 = sourceModel()->index(source_row, 7, source_parent);
    QModelIndex index8 = sourceModel()->index(source_row, 8, source_parent);
    QModelIndex index9 = sourceModel()->index(source_row, 9, source_parent);
    QModelIndex index10 = sourceModel()->index(source_row, 10, source_parent);
    QModelIndex index11 = sourceModel()->index(source_row, 11, source_parent);
    QModelIndex index19 = sourceModel()->index(source_row, 19, source_parent);
    QModelIndex index22 = sourceModel()->index(source_row, 22, source_parent);

    bool isGender;
    if (m_rxCol3=="请选择"){
        isGender = true;
    } else {
        isGender = sourceModel()->data(index3).toString().contains(m_rxCol3);
    }
    bool isWeight;
    if(m_rxCol4=="0.00"){
        isWeight = true;
    } else {
        isWeight = sourceModel()->data(index4).toString().contains(m_rxCol4);
    }
    bool isLevel;
    if(m_rxCol6=="请选择"){
        isLevel = true;
    } else {
        isLevel = sourceModel()->data(index6).toString().contains(m_rxCol6);
    }
    bool isTeam;
    if(m_rxCol7=="请选择"){
        isTeam = true;
    } else {
        isTeam = sourceModel()->data(index7).toString().contains(m_rxCol7);
    }
    bool isStrage;
    if(m_rxCol8=="请选择"){
        isStrage = true;
    } else {
        isStrage = sourceModel()->data(index8).toString().contains(m_rxCol8);
    }
    bool isStroke;
    if(m_rxCol9== "请选择"){
        isStroke = true;
    } else {
        isStroke = sourceModel()->data(index9).toString().contains(m_rxCol9);
    }
    bool isType;
    if(m_rxCol10=="请选择"){
        isType = true;
    } else {
        isType = sourceModel()->data(index10).toString().contains(m_rxCol10);
    }
    bool isDist;
    if(m_rxCol11=="请选择"){
        isDist = true;
    } else {
        isDist = sourceModel()->data(index11).toString().contains(m_rxCol11);
    }
    bool isEnv;
    if(m_rxCol19=="请选择"){
        isEnv = true;
    } else {
        isEnv = sourceModel()->data(index19).toString().contains(m_rxCol19);
    }


    if(m_refresh == "source"){
        return sourceModel()->data(index22).toString().contains(m_refresh);
    } else {
        return (isGender && isWeight && isLevel && isTeam && isStrage && isStroke && isType && isDist && isEnv);
    }
}


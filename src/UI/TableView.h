#ifndef TABLEVIEW_H
#define TABLEVIEW_H
#include <QObject>
#include <QRegExp>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QModelIndex>
#include <QMap>
#include <QString>
#include <QLabel>
#include <sstream>

#include "TableDelegate/SortFilterProxyModel.h"
#include "TableDelegate/TableData.h"
#include "src/Algorithm/kmeans.h"
#include "src/Algorithm/Score.h"
#include "src/Settings/TableSetting.h"
#include "src/UI/ClusterPage.h"
#include "src/UI/StatisticsPage.h"

class TableView: public QTableView
{
    Q_OBJECT    
    QStringList m_headerlist;
    QStandardItem *m_item;
    QStandardItemModel *m_model;
    QItemSelectionModel *m_selectModel;
    SortFilterProxyModel* m_proxyModel;
    int m_scoreMode = 0;
    int m_K;
    QMap<QString,bool> m_clusterItem;
    int m_iters;
    int m_historyRowCount = 1;
    QMap<QString,TableData*> m_allTableData;
    QMap<QString,QString> maxPowerKeyMap{
        {"自由泳-蹬边滑行","自配合"},{"自由泳-自腿","自配合"},{"自由泳-自手","自配合"},{"自由泳-自配合","自配合"},{"自由泳-海豚腿(俯卧)","自配合"},
        {"仰泳-蹬边滑行","仰配合"},{"仰泳-仰腿","仰配合"},{"仰泳-仰手","仰配合"},{"仰泳-仰配合","仰配合"},{"仰泳-海豚腿(仰卧)","仰配合"},
        {"蛙泳-蹬边滑行","蛙配合"},{"蛙泳-蛙腿","蛙配合"},{"蛙泳-蛙手","蛙配合"},{"蛙泳-蛙配合","蛙配合"},
        {"蝶泳-蹬边滑行","蝶配合"},{"蝶泳-蝶腿","蝶配合"},{"蝶泳-蝶手","蝶配合"},{"蝶泳-蝶配合","蝶配合"},{"蝶泳-海豚腿(俯卧)","蝶配合"}
    };
    QMap<QString,QString> contributionMap{
        {"自由泳","自腿-自手"},{"仰泳","仰腿-仰手"},{"蛙泳","蛙腿-蛙手"},{"蝶泳","蝶腿-蝶手"}
    };

    QStringList getHeaderData();
    int K();
    int Iters();
    QMap<QString,bool> clusterItem();
    stringstream _clusterItemsToSSteam(int rowIndex);
    QVector<QString> _staticstisResult(QVector<double> vec);
    TableSetting* tableSetting();
    int scoreMode();

public:
    explicit TableView(QObject *parent = 0);
    ~TableView();
    static TableView *getInstance();

    int rowCount();
    int historyRowCount();
    void setTableModel(int row, int column, QString cellvalue);
    void setHeaderModel(int column, QString cellvalue);
    void addRowData(QList<QStandardItem*> aItemList);
    void computedModel();
    void clusterModel();
    void statisticsModel();
    void setK(int k);
    void setIters(int iters);
    void setClusterItem(QMap<QString,bool> clusterItem);
    QStandardItemModel* model();
    SortFilterProxyModel* proxyModel();
    QVector<int> selectRowIndexs();
    QVector<int> searchRowIndexs();
    bool isExistsRecord(QString text);
    bool isExistsPerson(QString text);
    QMap<QString,QVector<int>> personStatistics();
    QMap<QString,QMap<QString,QVector<QVector<double>>>> singlePersonStatistics();

    QMap<QString,TableData*> tableDatas();
    void addTableData(QString person, QString weight, QString stroke,QString strokeItem, QString distance, QVector<double> values);
    void delTableData(QString person, QString stroke, QString strokeItem, QString distance);
    void delTableData(QString person);
    void updateTableData(QString person,QString stroke,QString strokeItem,QString distance, QVector<double> values);
    QVector<double> selTableData(QString person,QString stroke,QString strokeItem, QString distance);

public slots:
    void setScoreMode(int scoreMode);
};

//

class TableModelManager
{
private:
    QVector<TableView*> m_tableModels;
public:
    static TableModelManager *getInstance();
    explicit TableModelManager(QObject* parent = 0);
    void insertModel(TableView* tablemodel);
    void createModel();
    void delModel(int index);
    QVector<TableView*> getALLModels();
    TableView* getCurTableModel(int Index);
    int getTableModelCount();
};

#endif // TABLEVIEW_H

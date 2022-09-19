#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QFileDialog>
#include <QTableWidget>
#include <QStandardPaths>
#include <QPoint>

#include "xlsxdocument.h"
#include "xlsxworksheet.h"
#include "xlsxcellrange.h"
#include "xlsxformat.h"
#include "xlsxcell.h"

#include "src/UI/TableView.h"
#include "src/UI/ClusterPage.h"
#include "src/UI/StatisticsPage.h"
#include "src/Common/BasicTool.h"
#include "src/Common/Notice/Notification/ZpNotificationManager.h"

class Player: public QObject
{
    Q_OBJECT
    void _saveModel(QXlsx::Document& xlsx, QStandardItemModel* model);
    void _saveProxyModel(QXlsx::Document& xlsx, QStandardItemModel* model,QVector<int> rowIndexs);
public:
    static Player *getInstance();
    Player();
    QVector<QStringList> openXlsx();
    QVector<QVector<QString>> openScoreXlsx();
    void saveXlsx();
    void saveModelXlsx();
    void exportTemplate(QStringList sl_headerData);

    ZpNotificationManager* ZpNotificationManager();
private:
    QXlsx::Format m_cellFormat;
    QXlsx::Format m_headerFormat;
    QXlsx::Format _CellFormat();
    QXlsx::Format _HeaderFormat();
};

#endif // PLAYER_H

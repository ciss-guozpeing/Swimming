#include "Player.h"
#include <QDebug>

#include "src/Common/Message.h"
#include "src/Settings/TableSetting.h"
#include "src/UI/TableView.h"
#include "src/UI/ComputedPage.h"
#include "src/DB/Record.h"
#include "src/DB/Person.h"
#include "src/Settings/TableSetting.h"

using namespace QXlsx;

static Player* INSTANCE=nullptr;

Player::Player() {}

Player *Player::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new Player();
    }
    return INSTANCE;
}

void Player::openXlsx()
{
    QString filePath = QFileDialog::getOpenFileName(0, "Open xlsx file", QString(), "*.xlsx");

    auto tableView = TableView::getInstance();
    auto computedPage = ComputedPage::getInstance();
    auto tableSetting = TableSetting::getInstance();

    if (!filePath.isEmpty()) {
        QString cellValue;

        Document xlsx(filePath);
        xlsx.selectSheet(xlsx.sheetNames().at(0));

        int rowCount = xlsx.dimension().rowCount();
        int columnCount = xlsx.dimension().columnCount();

        for (int i = 2; i < rowCount + 1; i++) {
            QStringList cells;
            for (int j = 1; j < columnCount + 1; j++) {
                QXlsx::Cell *cell = xlsx.cellAt(i, j);
                if (cell == NULL){
                    cellValue = "";
                    cells.push_back(cellValue);
                } else {
                    cellValue = cell->value().toString();
                    if(cell->cellType() == 1){
                        cellValue = QString::number(cellValue.toDouble(),'f', 2);
                    }
                    cells.push_back(cellValue);
                }
            }
            cells.push_back("source");
            // 检测
            QString name = cells.at(2);
            QString birthday = cells.at(0).split("::").at(1);
            QString gender = cells.at(3);
            QString stroke = cells.at(9);
            QString strokeItem = cells.at(10);
            QString distance = cells.at(11);
            QString record = name + birthday + gender + stroke + strokeItem + distance;
            bool isExistsData = tableView->isExistsRecord(record);
            if(!isExistsData){
                QList<QStandardItem*> aItemList;
                for(int i=0;i<cells.length();i++){
                    QStandardItem* item = new QStandardItem(cells.at(i));
                    item->setTextAlignment(Qt::AlignCenter);
                    aItemList.append(item);
                }
                DB::Person* person = new DB::Person();
                DB::Record* record = new DB::Record();
                person->createPerson(aItemList.at(2)->text(),aItemList.at(0)->text().split("::").at(1),aItemList.at(3)->text(),aItemList.at(4)->text());
                record->createRecord(aItemList.at(2)->text(),aItemList.at(0)->text().split("::").at(1),aItemList.at(3)->text(),
                                     aItemList.at(6)->text(),aItemList.at(7)->text(),aItemList.at(8)->text(),aItemList.at(9)->text(),
                                     aItemList.at(10)->text(),aItemList.at(11)->text(),aItemList.at(12)->text(),aItemList.at(13)->text(),
                                     aItemList.at(14)->text(),aItemList.at(19)->text(),aItemList.at(1)->text().split("::").at(1));
                QString person_str = aItemList.at(2)->text()+ "-" + aItemList.at(3)->text()+ "-" + aItemList.at(0)->text().split("::").at(1);
                if(!tableView->isExistsPerson(person_str)){
                    computedPage->createSinglePersonChart(person_str);
                }
                tableView->addRowData(aItemList);
                QVector<double> values ={aItemList.at(12)->text().toDouble(),aItemList.at(13)->text().toDouble(),
                                         aItemList.at(14)->text().toDouble(),0,0,0,0};
                tableView->addTableData(person_str,aItemList.at(9)->text(),aItemList.at(10)->text(),aItemList.at(11)->text(),values);
                tableView->setColumnHidden(tableSetting->getTableHeaderData().length(), true);
                person->deleteLater();
                record->deleteLater();
            }


        }
    }
}

QVector<QVector<QString>> Player::openScoreXlsx()
{
    QString filePath = QFileDialog::getOpenFileName(0, "Open score xlsx file", QString(), "*.xlsx");
    QVector<QVector<QString>> scoreDatas;
    if (!filePath.isEmpty()) {
        QString cell_str;

        Document xlsx(filePath);
        xlsx.selectSheet(xlsx.sheetNames().at(0));

        int rowCount = xlsx.dimension().rowCount();
        int columnCount = xlsx.dimension().columnCount();

        for(int i=1; i<rowCount + 1; i++){
            QVector<QString> rowData;
            for(int j=1; j<columnCount+1; j++){
                QXlsx::Cell *cell = xlsx.cellAt(i, j);
                if (cell == NULL){
                    cell_str = "";
                    rowData.push_back(cell_str);
                } else {
                    cell_str = cell->value().toString();
                    if(cell->cellType() == 1){
                        cell_str = QString::number(cell_str.toDouble(),'f', 2);
                    }
                    rowData.push_back(cell_str);
                }
            }
            scoreDatas.append(rowData);
        }
    }
    return scoreDatas;
}

void Player::saveXlsx()
{
    auto tableSetting = TableSetting::getInstance();
    QXlsx::Document xlsx;
    QString filepath = QFileDialog::getSaveFileName(NULL, "save xlsx file", "", "xlsx(*.xlsx)");
    if (filepath != "") {
        auto model = TableView::getInstance()->model();
        int columnCount = tableSetting->getTableHeaderData().length() - 1;
        int rowCount = model->rowCount();
        // 表头数据
        for (int i = 0; i < columnCount; i++) {
           QString headerValue = model->horizontalHeaderItem(i)->text();
           xlsx.write(1, i + 1, headerValue, _HeaderFormat());
        }
        // 数据区
        for (int i = 1; i < rowCount + 1; i++)
        {
            for (int j = 0; j < columnCount; j++)
            {
                QString cellValue = model->item(i - 1, j)->text();
                xlsx.write(i + 1, j + 1, cellValue, _CellFormat());
            }
        }

        if (xlsx.saveAs(filepath)){
            ZpNotificationManager()->notify("保存文件","保存文件成功",":/images/images/success.png","");
        } else {
            ZpNotificationManager()->notify("保存文件","保存文件失败",":/images/images/failed.png","");
        }
    }

}

void Player::saveModelXlsx()
{
    auto tableView = TableView::getInstance();
    auto clusterPage = ClusterPage::getInstance();
    auto statisticsPage = StatisticsPage::getInstance();
    QXlsx::Document xlsx;
    QString filepath = QFileDialog::getSaveFileName(NULL, "save xlsx file", "", "xlsx(*.xlsx)");
    if (filepath != "" and tableView->searchRowIndexs().length() !=0) {
        if (!xlsx.selectSheet("原始表")) {
            xlsx.addSheet("原始表");
            this->_saveProxyModel(xlsx,tableView->model(), tableView->searchRowIndexs());
        } else {
            this->_saveProxyModel(xlsx,tableView->model(), tableView->searchRowIndexs());
        }
        if (!xlsx.selectSheet("聚类结果页")) {
            xlsx.addSheet("聚类结果页");
            this->_saveModel(xlsx, clusterPage->model());
        } else {
            this->_saveModel(xlsx, clusterPage->model());
        }

        if (!xlsx.selectSheet("统计结果页")) {
            xlsx.addSheet("统计结果页");
            this->_saveModel(xlsx, statisticsPage->model());
        } else {
            this->_saveModel(xlsx, statisticsPage->model());
        }
        bool isSave = xlsx.saveAs(filepath);
        if (isSave) {
            QString text = "保存文件成功";
            ZpNotificationManager()->notify("保存文件",text,":/images/images/success.png","");
        } else {
            QString text = "保存文件失败";
            ZpNotificationManager()->notify("保存文件",text,":/images/images/failed.png","");
        }
    } else{
        QString text = "保存文件失败";
        ZpNotificationManager()->notify("保存文件",text,":/images/images/failed.png","");
    }
}

void Player::_saveModel(QXlsx::Document& xlsx, QStandardItemModel* model)
{
    qDebug()<<model->rowCount() << model->columnCount();
    // 写入水平表头
    for(int i=0; i<model->columnCount(); i++){
        xlsx.write(1, i+2, model->horizontalHeaderItem(i)->text(),_HeaderFormat());
    }
    // 写入垂直表头
    for(int i=0; i<model->rowCount(); i++){
        xlsx.write(i+2, 1, model->verticalHeaderItem(i)->text(),_HeaderFormat());
    }
    // 写入内容
    for(int i=0; i<model->rowCount(); i++){
        for(int j=0; j<model->columnCount(); j++){
            xlsx.write(i+2,j+2, model->item(i,j)->text(),_CellFormat());
        }
    }
}

void Player::_saveProxyModel(QXlsx::Document& xlsx, QStandardItemModel* model,QVector<int> rowIndexs)
{

    // 写入水平表头
    for(int i=0; i<model->columnCount(); i++){
        xlsx.write(1, i+1,model->horizontalHeaderItem(i)->text(),_HeaderFormat());
    }
    // 写入内容
    if(!rowIndexs.isEmpty()){
        for(int i=0; i<rowIndexs.length(); i++){
            for(int j=0; j<model->columnCount(); j++){
                xlsx.write(i+2,j+1, model->item(rowIndexs.at(i),j)->text(),_CellFormat());
            }
        }
    }
    xlsx.setColumnHidden(23,true);
}

void Player::exportTemplate(QStringList sl_headerData)
{
    QString filename = "template.xlsx";
    QString location = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString filepath = location + "/"  + filename;
    QXlsx::Document xlsx;
    for (int i = 0; i<sl_headerData.length() - 3; i++) {
        xlsx.write(1, i + 1, sl_headerData.at(i), _HeaderFormat());
    }
    bool isSave = xlsx.saveAs(filepath);
    if (isSave) {
        QString text = "导出模版成功";
        ZpNotificationManager()->notify("保存文件",text,":/images/images/success.png","");
    } else {
        QString text = "导出模版失败";
        ZpNotificationManager()->notify("保存文件",text,":/images/images/failed.png","");
    }
}

QXlsx::Format Player::_CellFormat()
{
    m_cellFormat.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    return m_cellFormat;
}

QXlsx::Format Player::_HeaderFormat()
{
    m_headerFormat.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    return m_headerFormat;
}

ZpNotificationManager* Player::ZpNotificationManager()
{
    return ZpNotificationManager::getInstance();
}

#include "LoadTableData.h"
#include "src/UI/ComputedPage.h"
#include "src/DB/Record.h"
#include "src/DB/Person.h"
#include "src/UI/TableView.h"
#include "src/Settings/TableSetting.h"

QVector<QStringList> LoadTableDataRunable::m_tableDatas = {};
LoadTableDataRunable::LoadTableDataRunable(QObject *parent)
    : QObject{parent}
{
    auto record_db =new DB::Record;
    auto computedPage = ComputedPage::getInstance();
    connect(this,SIGNAL(createPersonChart(QString)),computedPage,SLOT(updatePersonChart(QString)));
    connect(this,SIGNAL(createRecordDB(QStringList)),record_db,SLOT(updateRecord(QStringList)));
}

void LoadTableDataRunable::run()
{
    auto tableView = TableView::getInstance();
    for(int i=0; i<m_tableDatas.size(); ++i){
        // 检测
        QVector<double> values;
        QString name = m_tableDatas.at(i).at(2);
        QString birthday = m_tableDatas.at(i).at(0).split("::").at(1);
        QString gender = m_tableDatas.at(i).at(3);
        QString weight = m_tableDatas.at(i).at(4);
        QString stroke = m_tableDatas.at(i).at(9);
        QString strokeItem = m_tableDatas.at(i).at(10);
        QString distance = m_tableDatas.at(i).at(11);
        QString maxPower1 = m_tableDatas.at(i).at(12);
        QString maxPower2 = m_tableDatas.at(i).at(13);
        QString maxPower3 = m_tableDatas.at(i).at(14);
        QString maxPower = m_tableDatas.at(i).at(15);
        QString relPower = m_tableDatas.at(i).at(16);
        QString percentage = m_tableDatas.at(i).at(17);
        QString contributionRate = m_tableDatas.at(i).at(18);
        values.push_back(maxPower1.toDouble());
        values.push_back(maxPower2.toDouble());
        values.push_back(maxPower3.toDouble());
        values.push_back(maxPower.toDouble());
        values.push_back(relPower.toDouble());
        values.push_back(percentage.toDouble());
        values.push_back(contributionRate.toDouble());
        QString person = name + "-" + gender + "-" + birthday;
        QString record = person + "-" + stroke + "-" + strokeItem + "-" + distance;
        bool isExistsRecord = tableView->isExistsRecord(record);
        bool isExistsPerson = tableView->isExistsPerson(person);
        if(!isExistsRecord){
            QList<QStandardItem*> aItemList;
            for(int j=0;j<m_tableDatas.at(i).length();j++){
                QStandardItem* item = new QStandardItem(m_tableDatas.at(i).at(j));
                item->setTextAlignment(Qt::AlignCenter);
                aItemList.append(item);
            }
            // 添加行数据
            tableView->addRowData(aItemList);
            // 添加数据结构
            tableView->addTableData(person, weight, stroke, strokeItem, distance, values);
            tableView->setColumnHidden(m_tableDatas.at(i).size()-1, true);
        }
        if(!isExistsPerson){
            emit createPersonChart(person);
        }
        // 发送数据库更新
        emit createRecordDB(m_tableDatas.at(i));
    }
}

void LoadTableDataRunable::receviedTableDatas(QVector<QStringList> tableDatas)
{
    m_tableDatas = tableDatas;
}

////                DB::Person* person = new DB::Person();
////                DB::Record* record = new DB::Record();
////                person->createPerson(aItemList.at(2)->text(),aItemList.at(0)->text().split("::").at(1),aItemList.at(3)->text(),aItemList.at(4)->text());
////                record->createRecord(aItemList.at(2)->text(),aItemList.at(0)->text().split("::").at(1),aItemList.at(3)->text(),
////                                     aItemList.at(6)->text(),aItemList.at(7)->text(),aItemList.at(8)->text(),aItemList.at(9)->text(),
////                                     aItemList.at(10)->text(),aItemList.at(11)->text(),aItemList.at(12)->text(),aItemList.at(13)->text(),
////                                     aItemList.at(14)->text(),aItemList.at(19)->text(),aItemList.at(1)->text().split("::").at(1));
////                QString person_str = aItemList.at(2)->text()+ "-" + aItemList.at(3)->text()+ "-" + aItemList.at(0)->text().split("::").at(1);
////                if(!tableView->isExistsPerson(person_str)){
////                    computedPage->createSinglePersonChart(person_str);
////                }

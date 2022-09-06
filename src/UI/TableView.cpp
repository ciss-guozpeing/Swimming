#include "TableView.h"

#include "src/Algorithm/statistics.h"
#include "src/Common/Message.h"
#include "src/Settings/TableSetting.h"
#include "TableDelegate/StrokeDelegate.h"
#include "TableDelegate/GenderDelegate.h"
#include "TableDelegate/DistanceDelegate.h"
#include "TableDelegate/TrainStageDelegate.h"
#include "TableDelegate/TeamDelegate.h"
#include "TableDelegate/LevelDelegate.h"
#include "TableDelegate/StrokeItemDelegate.h"
#include "TableDelegate/EnvDelegate.h"
#include "TableDelegate/ReadonlyDelegate.h"
#include "TableDelegate/WeightDelegate.h"
#include "TableDelegate/MaxPowerDelegate.h"
#include "TableDelegate/AgeDelegate.h"

#include <QMessageBox>
#include <QHeaderView>
#include <QDebug>

static TableView* INSTANCE=nullptr;
TableView::TableView(QObject *parent)
    :QTableView()
{
    Q_UNUSED(parent);
    m_model = new QStandardItemModel(this);
    m_proxyModel = new SortFilterProxyModel(this);
    m_selectModel = new QItemSelectionModel(m_proxyModel);
    m_proxyModel->setSourceModel(m_model);

    this->setModel(m_proxyModel);
    this->setSelectionModel(m_selectModel);

    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);

//    auto strokeDelegate = StrokeDelegate::getInstance();
    auto genderDelegate = new GenderDelegate();
    auto weigthDelegate = new WeightDelegate();
    auto ageDelegate = new AgeDelegate();
    auto distanceDelegate = new DistanceDelegate();
    auto trainStageDelegate = new TrainStageDelegate();
    auto teamDelegate = new TeamDelegate();
    auto levelDelegate = new LevelDelegate();
    auto envDelegate = new EnvDelegate();
//    auto strokeItemDelegate = new StrokeItemDelegate();
    auto maxPowerDelegate = new MaxPowerDelegate();
    auto readOnlyDelegate = new ReadOnlyDelegate();

    this->setItemDelegateForColumn(0, readOnlyDelegate);
    this->setItemDelegateForColumn(1, readOnlyDelegate);
    this->setItemDelegateForColumn(2, readOnlyDelegate);
    this->setItemDelegateForColumn(3, genderDelegate);
    this->setItemDelegateForColumn(4, weigthDelegate);
    this->setItemDelegateForColumn(5, ageDelegate);
    this->setItemDelegateForColumn(6, levelDelegate);
    this->setItemDelegateForColumn(7, teamDelegate);
    this->setItemDelegateForColumn(8, trainStageDelegate);
    this->setItemDelegateForColumn(9, readOnlyDelegate);
    this->setItemDelegateForColumn(10, readOnlyDelegate);
    this->setItemDelegateForColumn(11, distanceDelegate);
    this->setItemDelegateForColumn(12, maxPowerDelegate);
    this->setItemDelegateForColumn(13, maxPowerDelegate);
    this->setItemDelegateForColumn(14, maxPowerDelegate);
    this->setItemDelegateForColumn(15, readOnlyDelegate);
    this->setItemDelegateForColumn(16, readOnlyDelegate);
    this->setItemDelegateForColumn(17, readOnlyDelegate);
    this->setItemDelegateForColumn(18, readOnlyDelegate);
    this->setItemDelegateForColumn(19, envDelegate);
}

TableView::~TableView()
{
    deleteLater();
}

TableView *TableView::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new TableView();
    }
    return INSTANCE;
}

int TableView::rowCount()
{
    return m_model->rowCount();
}

int TableView::historyRowCount()
{
    return m_historyRowCount;
}

void TableView::setTableModel(int row, int column, QString cellvalue)
{
    QStandardItem* item = new QStandardItem(cellvalue);
    item->setTextAlignment (Qt::AlignHCenter | Qt::AlignVCenter);
    m_model->setItem(row, column, item);

}

void TableView::setHeaderModel(int column, QString cellvalue)
{
    QStandardItem* item = new QStandardItem(cellvalue);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_model->setHorizontalHeaderItem(column,item);
    this->setColumnHidden(20,true);
    this->setColumnHidden(21,true);
    this->setColumnHidden(22,true);
}

QStringList TableView::getHeaderData()
{
    QStandardItem* hItem;
    QStringList headerdata;
    int columnCount = m_model->columnCount();
    for (int i = 0; i < columnCount; ++i)
    {
        hItem=m_model->horizontalHeaderItem(i);
        headerdata.append(hItem->text());
    }
    return headerdata;
}

QStandardItemModel* TableView::model()
{
    return m_model;
}

SortFilterProxyModel* TableView::proxyModel()
{
    return m_proxyModel;
}

void TableView::addRowData(QList<QStandardItem *> aItemList)
{
    m_historyRowCount += 1;
    m_model->insertRow(m_model->rowCount(),aItemList);
}

QVector<int> TableView::selectRowIndexs()
{
    QVector<int> rowIndex;
    for(int i=0; i<m_selectModel->selectedRows().size(); i++){
       int index = m_proxyModel->mapToSource(m_selectModel->selectedRows().at(i)).row();
       rowIndex.push_back(index);
    }
    return rowIndex;
}

QVector<int> TableView::searchRowIndexs()
{
    QVector<int> rowIndex;
    for(int i=0; i<m_proxyModel->rowCount(); ++i){
        int index = m_proxyModel->mapToSource(m_proxyModel->index(i,2)).row();
        rowIndex.push_back(index);
    }
    return rowIndex;
}

bool TableView::isExistsRecord(QString text)
{
    QVector<QString> rowDataVecotr;
    for(int i=0; i<m_model->rowCount(); ++i){
        QString name = m_model->item(i,2)->text();
        QString birthday = m_model->item(i,0)->text().split("::").at(1);
        QString gender = m_model->item(i,3)->text();
        QString stroke = m_model->item(i,9)->text();
        QString strokeItem = m_model->item(i,10)->text();
        QString distance = m_model->item(i,11)->text();
        QString record = name + birthday + gender + stroke + strokeItem + distance;
        rowDataVecotr.push_back(record);
    }
    if(rowDataVecotr.contains(text)){
        return true;
    } else {
        return false;
    }
}

bool TableView::isExistsPerson(QString text)
{
    QVector<QString> rowDataVector;
    for(int i=0; i<model()->rowCount(); ++i){
        QString name = model()->item(i,2)->text();
        QString gender = model()->item(i,3)->text();
        QString birthday = m_model->item(i,0)->text().split("::").at(1);
        QString person = name + "-" + gender + "-" + birthday;
        rowDataVector.push_back(person);
    }
    if(rowDataVector.contains(text)){
        return true;
    } else {
        return false;
    }
}

QMap<QString,QVector<int>> TableView::personStatistics()
{
    QVector<QString> personTotal;
    QVector<QString> manTotal;
    QVector<QString> womanTotal;
    QVector<QString> man_breaststrokeTotal; // 蛙泳
    QVector<QString> woman_breaststrokeTotal;
    QVector<QString> man_butterflyStrokeTotal; // 蝶泳
    QVector<QString> woman_butterflyStrokeTotal;
    QVector<QString> man_backStrokeTotal;  //仰泳
    QVector<QString> woman_backStrokeTotal;
    QVector<QString> man_freeStrokeTotal;  // 自由泳
    QVector<QString> woman_freeStrokeTotal;

    for(int i=0; i<model()->rowCount(); ++i){
        QString name = m_model->item(i,2)->text();
        QString gender = m_model->item(i,3)->text();
        QString birthday = m_model->item(i,0)->text().split("::").at(1);
        QString stroke = m_model->item(i,9)->text();
        QString person = name +birthday + gender;
        QString personGender = name+gender+birthday;
        QString personGenderStroke = name + gender + birthday + stroke;
        personTotal.push_back(person);
        if(gender=="男"){
            manTotal.push_back(personGender);
        }
        if(gender=="女"){
            womanTotal.push_back(personGender);
        }
        if(gender=="男" && stroke=="蛙泳"){            // 蛙泳
            man_breaststrokeTotal.push_back(personGenderStroke);
        }
        if(gender=="女" && stroke=="蛙泳"){
            woman_breaststrokeTotal.push_back(personGenderStroke);
        }

        if(gender=="男" && stroke=="蝶泳"){
            man_butterflyStrokeTotal.push_back(personGenderStroke);
        }
        if(gender=="女" && stroke=="蝶泳"){
            woman_butterflyStrokeTotal.push_back(personGenderStroke);
        }
        if(gender=="男" && stroke=="仰泳"){
            man_backStrokeTotal.push_back(personGenderStroke);
        }
        if(gender=="女" && stroke=="仰泳"){
            woman_backStrokeTotal.push_back(personGenderStroke);
        }
        if(gender=="男" && stroke=="自由泳"){
            man_freeStrokeTotal.push_back(personGenderStroke);
        }
        if(gender=="女" && stroke=="自由泳"){
            woman_freeStrokeTotal.push_back(personGenderStroke);
        }
    }
    sort(personTotal.begin(),personTotal.end());
    auto personTotal_int = unique(personTotal.begin(),personTotal.end());
    personTotal.erase(personTotal_int,personTotal.end());

    sort(manTotal.begin(),manTotal.end());
    auto manTotal_int = unique(manTotal.begin(), manTotal.end());
    manTotal.erase(manTotal_int,manTotal.end());
    sort(womanTotal.begin(), womanTotal.end());
    auto womanTotal_int = unique(womanTotal.begin(), womanTotal.end());
    womanTotal.erase(womanTotal_int,womanTotal.end());


    sort(man_backStrokeTotal.begin(),man_backStrokeTotal.end());
    auto man_backStrokeTotal_int = unique(man_backStrokeTotal.begin(), man_backStrokeTotal.end());
    man_backStrokeTotal.erase(man_backStrokeTotal_int,man_backStrokeTotal.end());
    sort(woman_backStrokeTotal.begin(),woman_backStrokeTotal.end());
    auto woman_backStrokeTotal_int = unique(woman_backStrokeTotal.begin(),woman_backStrokeTotal.end());
    woman_backStrokeTotal.erase(woman_backStrokeTotal_int,woman_backStrokeTotal.end());

    sort(man_freeStrokeTotal.begin(),man_freeStrokeTotal.end());
    auto man_freeStrokeTotal_int = unique(man_freeStrokeTotal.begin(), man_freeStrokeTotal.end());
    man_freeStrokeTotal.erase(man_freeStrokeTotal_int,man_freeStrokeTotal.end());
    sort(woman_freeStrokeTotal.begin(),woman_freeStrokeTotal.end());
    auto woman_freeStrokeTotal_int = unique(woman_freeStrokeTotal.begin(),woman_freeStrokeTotal.end());
    woman_freeStrokeTotal.erase(woman_freeStrokeTotal_int,woman_freeStrokeTotal.end());

    sort(man_butterflyStrokeTotal.begin(),man_butterflyStrokeTotal.end());
    auto man_butterflyStrokeTotal_int = unique(man_butterflyStrokeTotal.begin(), man_butterflyStrokeTotal.end());
    man_butterflyStrokeTotal.erase(man_butterflyStrokeTotal_int,man_butterflyStrokeTotal.end());
    sort(woman_butterflyStrokeTotal.begin(),woman_butterflyStrokeTotal.end());
    auto woman_butterflyStrokeTotal_int = unique(woman_butterflyStrokeTotal.begin(),woman_butterflyStrokeTotal.end());
    woman_butterflyStrokeTotal.erase(woman_butterflyStrokeTotal_int,woman_butterflyStrokeTotal.end());

    sort(man_breaststrokeTotal.begin(),man_breaststrokeTotal.end());
    auto man_breaststrokeTotal_int = unique(man_breaststrokeTotal.begin(), man_breaststrokeTotal.end());
    man_breaststrokeTotal.erase(man_breaststrokeTotal_int,man_breaststrokeTotal.end());
    sort(woman_breaststrokeTotal.begin(),woman_breaststrokeTotal.end());
    auto woman_breaststrokeTotal_int = unique(woman_breaststrokeTotal.begin(),woman_breaststrokeTotal.end());
    woman_breaststrokeTotal.erase(woman_breaststrokeTotal_int,woman_breaststrokeTotal.end());

    int personCount = personTotal.size();
    int womanCount = womanTotal.size();
    int manCount = manTotal.size();
    QVector<int> person;
    QVector<int> butterflyStroke;
    QVector<int> backStroke;
    QVector<int> breastStroke;
    QVector<int> freeStroke;
    person.push_back(personCount);
    person.push_back(manCount);
    person.push_back(womanCount);
    butterflyStroke.push_back(man_butterflyStrokeTotal.size()+woman_butterflyStrokeTotal.size());
    butterflyStroke.push_back(man_butterflyStrokeTotal.size());
    butterflyStroke.push_back(woman_butterflyStrokeTotal.size());
    backStroke.push_back(man_backStrokeTotal.size()+woman_backStrokeTotal.size());
    backStroke.push_back(man_backStrokeTotal.size());
    backStroke.push_back(woman_backStrokeTotal.size());
    breastStroke.push_back(man_breaststrokeTotal.size() + woman_breaststrokeTotal.size());
    breastStroke.push_back(man_breaststrokeTotal.size());
    breastStroke.push_back(woman_breaststrokeTotal.size());
    freeStroke.push_back(woman_freeStrokeTotal.size() + man_freeStrokeTotal.size());
    freeStroke.push_back(man_freeStrokeTotal.size());
    freeStroke.push_back(woman_freeStrokeTotal.size());
    QMap<QString,QVector<int>> result;
    result["总人数"]=person;
    result["蝶泳"]= butterflyStroke;
    result["仰泳"]= backStroke;
    result["自由泳"] = freeStroke;
    result["蛙泳"] = breastStroke;

    return result;
}

QMap<QString,QMap<QString,QVector<QVector<double>>>> TableView::singlePersonStatistics()
{
    QMap<QString,QMap<QString,QVector<QVector<double>>>> result;

    QStringList strokes = { "仰泳" , "蛙泳" , "蝶泳" ,"自由泳"};
    QMap<QString,QVector<QString>> strokeItems = {{"仰泳",{"仰腿","仰手","仰配合","蹬边滑行","海豚腿(仰卧)"}},
                                                  {"蛙泳",{"蛙腿","蛙手","蛙配合","蹬边滑行","海豚腿"}},
                                                  {"蝶泳",{"蝶腿","蝶手","蝶配合","蹬边滑行","海豚腿(俯卧)"}},
                                                  {"自由泳",{"自腿","自手","自配合","蹬边滑行","海豚腿(俯卧)"}}};
    QMap<QString,TableData*>::Iterator iter;


    for(iter=m_allTableData.begin();iter!=m_allTableData.end();iter++){
        QMap<QString,QVector<QVector<double>>> values1;
        QVector<QVector<double>> values11_5;
        QVector<QVector<double>> values11_7;
        QVector<double> values1_5;
        QVector<double> values1_7;
        QVector<double> values2_5;
        QVector<double> values2_7;
        QVector<double> values3_5;
        QVector<double> values3_7;
        QVector<double> values4_5;
        QVector<double> values4_7;
        QVector<double> values5_5;
        QVector<double> values5_7;
        for(int i=0;i<strokes.size();i++){
            for(int j=0;j<strokeItems[strokes.at(i)].size();j++){
                if(j==0){
                    double value_5 = iter.value()->Values(strokes.at(i),strokeItems[strokes.at(i)].at(j),"5").at(3);
                    double value_7 = iter.value()->Values(strokes.at(i),strokeItems[strokes.at(i)].at(j),"7").at(3);
                    values1_5.push_back(value_5);
                    values1_7.push_back(value_7);
                }
                if(j==1){
                    double value_5 = iter.value()->Values(strokes.at(i),strokeItems[strokes.at(i)].at(j),"5")[3];
                    double value_7 = iter.value()->Values(strokes.at(i),strokeItems[strokes.at(i)].at(j),"7")[3];
                    values2_5.push_back(value_5);
                    values2_7.push_back(value_7);
                }
                if(j==2){
                    double value_5 = iter.value()->Values(strokes.at(i),strokeItems[strokes.at(i)].at(j),"5")[3];
                    double value_7 = iter.value()->Values(strokes.at(i),strokeItems[strokes.at(i)].at(j),"7")[3];
                    values3_5.push_back(value_5);
                    values3_7.push_back(value_7);
                }
                if(j==3){
                    double value_5 = iter.value()->Values(strokes.at(i),strokeItems[strokes.at(i)].at(j),"5")[3];
                    double value_7 = iter.value()->Values(strokes.at(i),strokeItems[strokes.at(i)].at(j),"7")[3];
                    values4_5.push_back(value_5);
                    values4_7.push_back(value_7);
                }
                if(j==4){
                    if(iter.value()->Values(strokes.at(i),strokeItems[strokes.at(i)].at(j),"5").size()==7){
                        double value_5 = iter.value()->Values(strokes.at(i),strokeItems[strokes.at(i)].at(j),"5")[3];
                        double value_7 = iter.value()->Values(strokes.at(i),strokeItems[strokes.at(i)].at(j),"7")[3];
                        values5_5.push_back(value_5);
                        values5_7.push_back(value_7);
                    }
                    if(iter.value()->Values(strokes.at(i),strokeItems[strokes.at(i)].at(j),"5").size()==0){
                        values5_5.push_back(0);
                        values5_7.push_back(0);
                    }
                }
            }
        }
        values11_5.push_back(values1_5);
        values11_7.push_back(values1_7);
        values11_5.push_back(values2_5);
        values11_7.push_back(values2_7);
        values11_5.push_back(values3_5);
        values11_7.push_back(values3_7);
        values11_5.push_back(values4_5);
        values11_7.push_back(values4_7);
        values11_5.push_back(values5_5);
        values11_7.push_back(values5_7);

        values1.insert("5",values11_5);
        values1.insert("7",values11_7);

        result.insert(iter.key(),values1);
    }
    qDebug() <<"result" <<result;
    return result;
}

int TableView::K()
{
    return m_K;
}

void TableView::setK(int k)
{
    m_K = k;
}

int TableView::Iters()
{
    return m_iters;
}

void TableView::setIters(int iters)
{
    m_iters = iters;
}

QMap<QString,bool> TableView::clusterItem()
{
    return m_clusterItem;
}

void TableView::setClusterItem(QMap<QString,bool> clusterItem)
{
    m_clusterItem = clusterItem;
}

int TableView::scoreMode()
{
    return m_scoreMode;
}

void TableView::setScoreMode(int socreMode)
{
    m_scoreMode = socreMode;
}

void TableView::computedModel()
{
    auto statistics = Statistics::getInstance();
    auto tableSetting = TableSetting::getInstance();

    int rowCount = m_model->rowCount();
    QMap<QString,int> headerIndex = tableSetting->getHeaderIndex();
    int i_maxPowerIndex = headerIndex["maxpower_index"];
    int i_relPowerIndex = headerIndex["relpower_index"];
    int i_maxPower1Index = headerIndex["maxpowerone_index"];
    int i_maxPower2Index = headerIndex["maxpowertwo_index"];
    int i_maxPower3Index = headerIndex["maxpowerthree_index"];
    int i_penPowerIndex = headerIndex["percentage_index"];
    int i_weightIndex = headerIndex["weigth_idnex"];
    int i_identityIDIndex = headerIndex["identityID_index"];
    int i_strokeIndex = headerIndex["stroke_index"];
    int i_strokeItemIndex = headerIndex["strokeitem_index"];
    int i_contributeIndex = headerIndex["contribute_index"];

    QList<int> l_maxPowerIndex;
    l_maxPowerIndex.push_back(i_maxPower1Index);
    l_maxPowerIndex.push_back(i_maxPower2Index);
    l_maxPowerIndex.push_back(i_maxPower3Index);

    // 求最大力和相对力
    for (int i = 0; i < rowCount; i++) {
        QVector<double> v_maxPower;
        for (int j = 0; j < l_maxPowerIndex.length(); j++) {
            QString value = m_model->item(i,l_maxPowerIndex[j])->text();
            v_maxPower.append(value.toDouble());
        }
        QString weight = m_model->item(i,i_weightIndex)->text();
        QString maxPower = statistics->getMaxPower(v_maxPower);
        QString relPower = statistics->getRelativePower(maxPower,weight);
        this->setTableModel(i, i_maxPowerIndex, maxPower);
        this->setTableModel(i, i_relPowerIndex, relPower);
    }
    // 求百分比和贡献率
    QMap<QString,QString> m_rowMaxPowerValue;
    QList<QList<QString>> l_rowMaxPowerValue;
    for (int i = 0; i < rowCount; i++) {
        QString identityID = m_model->item(i,i_identityIDIndex)->text();
        QString stroke = m_model->item(i,i_strokeIndex)->text();
        QString strokeItem = m_model->item(i,i_strokeItemIndex)->text();
        QString distance = m_model->item(i,11)->text();
        QString record = identityID + "-" +  stroke + "-" + strokeItem + "-" + distance;

        QList<QString> recordAndMax;
        recordAndMax.append(record);
        recordAndMax.append(m_model->item(i,i_maxPowerIndex)->text());
        l_rowMaxPowerValue.append(recordAndMax);
        m_rowMaxPowerValue.insert(record,m_model->item(i,i_maxPowerIndex)->text());
    }
    for (int i=0; i<l_rowMaxPowerValue.length(); i++){
        QStringList strSplit = l_rowMaxPowerValue.at(i)[0].split("-");
        QString strokeItem = maxPowerKeyMap[strSplit[1] + "-" + strSplit[2]];
        QStringList strokeItems  = contributionMap[strSplit[1]].split("-");

        double legValue = m_rowMaxPowerValue[strSplit.at(0) + "-" +strSplit[1] + "-" + strokeItems.value(0) + "-" + strSplit.at(3) ].toDouble();
        double handleValue = m_rowMaxPowerValue[strSplit.at(0) + "-" +strSplit[1] + "-" + strokeItems.value(1) + "-" +strSplit.at(3)].toDouble();
        QString maxPower = m_rowMaxPowerValue[strSplit.at(0) + "-" +strSplit.at(1) + "-" + strokeItem + "-" + strSplit.at(3)];
        QString percentage,contributeRate;
        // 百分比
        if (maxPower == "") {
            percentage = "";
        } else {
            percentage = statistics->getPercentage(l_rowMaxPowerValue.at(i)[1], maxPower);
            percentage = QString::number(percentage.toDouble() * 100, 'f', 3) + '%';
        }
        // 贡献率
        if (legValue+handleValue == 0) {
            contributeRate = "";
        } else {
            contributeRate = statistics->getContribute(l_rowMaxPowerValue.at(i)[1], legValue + handleValue);
            contributeRate = QString::number(contributeRate.toDouble() * 100, 'f', 3) + '%';
        }
        qDebug() << maxPower;
        qDebug() << l_rowMaxPowerValue;
        // 设置
        this->setTableModel(i,i_penPowerIndex,percentage);
        this->setTableModel(i,i_contributeIndex,contributeRate);
    }

    // 重置数据
    for(int i=0; i<m_model->rowCount(); ++i){
        QVector<double> values;
        QString name = m_model->index(i,2).data().toString();
        QString birthday = m_model->index(i,0).data().toString().split("::").at(1);
        QString gender = m_model->index(i,3).data().toString();
        QString person = name+ "-" + gender + "-" + birthday;
        QString stroke = m_model->index(i,9).data().toString();
        QString strokeItem = m_model->index(i,10).data().toString();
        QString distance = m_model->index(i,11).data().toString();
        values.push_back(m_model->index(i,12).data().toDouble());
        values.push_back(m_model->index(i,13).data().toDouble());
        values.push_back(m_model->index(i,14).data().toDouble());
        values.push_back(m_model->index(i,15).data().toDouble());
        values.push_back(m_model->index(i,16).data().toDouble());
        values.push_back(m_model->index(i,17).data().toDouble());
        values.push_back(m_model->index(i,18).data().toDouble());
        m_allTableData[person]->setValues(stroke,strokeItem,distance, values);
    }


    // 求分数
    auto score = Score::getInstance();
    if(!m_scoreMode){
        if(!tableDatas().isEmpty()){
            score->setScoreTeamStandard(tableDatas());
        }
        for(int i=0; i<rowCount;i++){
            QString gender = model()->item(i, 3)->text();
            QString stroke = model()->item(i, 9)->text();
            QString strokeItem   = model()->item(i, 10)->text();
            QString distance = model()->item(i, 11)->text();
            QString maxPower = model()->item(i,15)->text();
            QString result = score->teamModelScore(gender, stroke, strokeItem, distance, maxPower);
            this->setColumnHidden(20, false);
            this->setTableModel(i,20,result);
        }
    }
    if(m_scoreMode)   {
        for(int i=0; i<rowCount; i++){
            QString gender = model()->item(i, 3)->text();
            QString stroke = model()->item(i, 9)->text();
            QString strokeItem   = model()->item(i, 10)->text();
            QString maxPower = model()->item(i,15)->text();
            QString result = score->commonModeScore(gender, stroke, strokeItem, maxPower);
            this->setColumnHidden(20, false);
            this->setTableModel(i,20,result);
        }
    }
}

void TableView::clusterModel()
{
    QVector<int> rowIndexs = searchRowIndexs();
    this->setColumnHidden(21, false);

    vector<Point> all_points;

    for (int i = 0; i < proxyModel()->rowCount(); ++i) {
        std::stringstream sstream = _clusterItemsToSSteam(rowIndexs.at(i));
        Point point(i, sstream.str());
        all_points.push_back(point);
    }
    if(K()!=0){
        Kmeans kmeans(K(), Iters());
        kmeans.run(all_points);

        // 写入结果
        for (int i=0; i<K(); i++)
        {
            int size = kmeans.clusters[i].getSize(); //某类有几个点
            for (int j = 0; j < size; j++)
            {
                int rowIndex = searchRowIndexs().at(kmeans.clusters[i].getPoint(j).getID()) ;
                QStandardItem* aItem = new QStandardItem(QString::number(i+1)); // 第几类
                aItem->setTextAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
                model()->setItem(rowIndex, 21, aItem);
            }
        }
        // 写入中心点
        auto clusterPage = ClusterPage::getInstance();
        vector<int> centorPoint = kmeans.getCenterPoint();
        int rowCount = centorPoint.size();
        for (int i=0; i<rowCount; i++){
            int rowIndex = searchRowIndexs().at(centorPoint[i]);
            QString rowHeader = QString("第%1类中心点数据").arg(i+1);
            clusterPage->model()->setVerticalHeaderItem(i,new QStandardItem(rowHeader));
            for (int j=0; j<clusterPage->model()->columnCount(); j++) {// 设置数据
                QStandardItem* aItem = new QStandardItem(model()->item(rowIndex,j)->text());
                aItem->setTextAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
                clusterPage->model()->setItem(i,j,aItem);
            }
        }
    }
}

stringstream TableView::_clusterItemsToSSteam(int rowIndex)
{
    std::string  nullStr = " ";
    QMap<QString,int> headerIndex = tableSetting()->getHeaderIndex();
    int i_maxPowerIndex = headerIndex["maxpower_index"];
    int i_relPowerIndex = headerIndex["relpower_index"];
    int i_percentageIndex = headerIndex["percentage_index"];
    int i_contributeIndex = headerIndex["contribute_index"];
    std::stringstream sstream;
    bool isSelMaxPower = clusterItem()["maxPower"];
    if (isSelMaxPower) {
        QString value = model()->item(rowIndex,i_maxPowerIndex)->text();
        sstream<< value.toStdString();
    }
    bool isSelRelPower =  clusterItem()["relPower"];
    if (isSelRelPower) {
        QString value = model()->item(rowIndex,i_relPowerIndex)->text();
        sstream<< nullStr + value.toStdString();
    }
    bool isSelPerage = clusterItem()["percentage"];
    if (isSelPerage) {
        QString value = model()->item(rowIndex,i_percentageIndex)->text();
        if (value != "") {
            double value_d = value.remove("%").toDouble();
            value = QString::number(value_d / 100);
        }
        sstream<< nullStr+ value.toStdString();
    }
    bool isSelContribution = clusterItem()["contribution"];
    if (isSelContribution) {
        QString value = model()->item(rowIndex,i_contributeIndex)->text();
        if (value != ""){
            double value_d = value.remove("%").toDouble();
            value = QString::number(value_d / 100);
        }
        sstream<< nullStr + value.toStdString();
    }
    return sstream;
}

void TableView::statisticsModel()
{
    auto statisticsPage = StatisticsPage::getInstance();
    QMap<QString,int> headerIndex = tableSetting()->getHeaderIndex();
    int i_maxpower_index = headerIndex["maxpower_index"];
    int i_relpower_index = headerIndex["relpower_index"];
    int i_percentage_index = headerIndex["percentage_index"];
    int i_contribute_index = headerIndex["contribute_index"];

    QVector<double> maxPower,relPower,percentage,contribute;

    for (int i=0; i<proxyModel()->rowCount(); i++) {
        maxPower.push_back(model()->item(searchRowIndexs().at(i),i_maxpower_index)->text().toDouble());
        relPower.push_back(model()->item(searchRowIndexs().at(i),i_relpower_index)->text().toDouble());
        QString percenageValue = model()->item(searchRowIndexs().at(i),i_percentage_index)->text();
        QString contributeValue = model()->item(searchRowIndexs().at(i),i_contribute_index)->text();
        if (percenageValue != "") {
             percenageValue = percenageValue.remove('%');
        }
        if (contributeValue !="") {
            contributeValue = contributeValue.remove('%');
        }
        percentage.push_back(percenageValue.toDouble() / 100);
        contribute.push_back(contributeValue.toDouble() / 100);
    }

    QVector<QVector<double>> statisticData;
    statisticData.push_back(maxPower);
    statisticData.push_back(relPower);
    statisticData.push_back(percentage);
    statisticData.push_back(contribute);
    for (int i=0; i<statisticsPage->model()->columnCount(); i++) {
        QVector<double> vec = statisticData[i];
        QVector<QString> statistics_res = _staticstisResult(vec);
        for (int j=0; j<statisticsPage->model()->rowCount(); j++) {
            QStandardItem* item = new QStandardItem(statistics_res[j]);
            item->setTextAlignment(Qt::AlignCenter);
            statisticsPage->model()->setItem(j,i,item);
        }
    }
}

QVector<QString> TableView::_staticstisResult(QVector<double> vec)
{
    auto statistics = Statistics::getInstance();
    QVector<QString> statistics_res;
    QString maxValue = statistics->getMaxValue(vec);
    QString minVluae = statistics->getMinValue(vec);
    QString averageValue = statistics->getAverageValue(vec);
    QString standardValue = statistics->getStandardDev(vec);
    statistics_res.push_back(maxValue);
    statistics_res.push_back(minVluae);
    statistics_res.push_back(averageValue);
    statistics_res.push_back(standardValue);
    return statistics_res;
}

TableSetting* TableView::tableSetting()
{
    return TableSetting::getInstance();
}

QMap<QString,TableData*> TableView::tableDatas()
{
    return m_allTableData;
}

void TableView::addTableData(QString person,QString stroke,QString strokeItem,QString distance,QVector<double> values)
{
    if(m_allTableData.contains(person)){
        m_allTableData[person]->setValues(stroke,strokeItem,distance,values);
    } else {
        TableData* tableData = new TableData(person,stroke,strokeItem, distance, values);
        m_allTableData.insert(person,tableData);
    }
}

void TableView::delTableData(QString person,QString stroke,QString strokeItem,QString distance)
{
    if(tableDatas().contains(person)){
        tableDatas()[person]->Values(stroke, strokeItem, distance) = {0,0,0,0,0,0,0};
    }
}

void TableView::delTableData(QString person)
{
    if(tableDatas().contains(person)){
        tableDatas().remove(person);
    }
}


//********************************************************//
// tableview manager class
//********************************************************//
static TableModelManager* INSTANCE_Manager=nullptr;

TableModelManager::TableModelManager(QObject *parent)
{
    Q_UNUSED(parent);
}

TableModelManager *TableModelManager::getInstance()
{
    if (!INSTANCE_Manager) {
        INSTANCE_Manager = new TableModelManager();
    }
    return INSTANCE_Manager;
}

void TableModelManager::createModel()
{
}

void TableModelManager::insertModel(TableView *tablemodel)
{
    m_tableModels.push_back(tablemodel);
}

void TableModelManager::delModel(int index)
{
    m_tableModels.removeAt(index);
}

QVector<TableView*> TableModelManager::getALLModels()
{
    return m_tableModels;
}

int TableModelManager::getTableModelCount()
{
    return m_tableModels.length();
}

TableView* TableModelManager::getCurTableModel(int Index)
{
    TableView* tablemodel = m_tableModels.at(Index);
    return tablemodel;
}

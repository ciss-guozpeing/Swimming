#include "ComputedPage.h"
#include "ui_computedpage.h"

static ComputedPage* INSTANCE=nullptr;

ComputedPage::ComputedPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComputedPage)
{
    ui->setupUi(this);
    this->personStatistics();
}

ComputedPage::~ComputedPage()
{
    delete ui;
}

ComputedPage *ComputedPage::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new ComputedPage();
    }
    return INSTANCE;
}

void ComputedPage::personStatistics()
{
    m_set0 = new QBarSet("总人数");
    m_set1 = new QBarSet("自由泳人数");
    m_set2 = new QBarSet("仰泳人数");
    m_set3 = new QBarSet("蛙泳人数");
    m_set4 = new QBarSet("蝶泳人数");
    *m_set0 << 0<<0<<0;
    *m_set1 << 0<<0<<0;
    *m_set2 << 0<<0<<0 ;
    *m_set3 << 0<<0<<0;
    *m_set4 << 0<<0<<0 ;
    m_series = new QBarSeries();

    m_series->append(m_set0);
    m_series->append(m_set1);
    m_series->append(m_set2);
    m_series->append(m_set3);
    m_series->append(m_set4);
    m_series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
    m_series->setLabelsFormat("@value");
    m_series->setLabelsVisible(true);
    m_set0->setLabelColor(Qt::black);
    m_set1->setLabelColor(Qt::black);
    m_set2->setLabelColor(Qt::black);
    m_set3->setLabelColor(Qt::black);
    m_set4->setLabelColor(Qt::black);


    QChart *chart = new QChart();
    chart->addSeries(m_series);
    chart->setTitle("人数分布统计柱状图");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "总人数分布" << "男性人数分布" << "女性人数分布";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    m_axisY = new QValueAxis;
    axisX->append(categories);
    m_axisY->setMin(0);
    m_axisY->setMax(1);
    m_axisY->setTitleText("人数");
    chart->addAxis(m_axisY,Qt::AlignLeft);
    chart->addAxis(axisX, Qt::AlignBottom);
    m_series->attachAxis(m_axisY);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignTop);
    m_barView = new QChartView();
    m_barView->setChart(chart);
    m_barView->setFixedHeight(600);
    m_barView->setRenderHint(QPainter::Antialiasing);
    ui->hLayout->addWidget(m_barView);
}

void ComputedPage::createSinglePersonChart(QString key)
{
    QString key_5 = key + "-5";
    QString key_7 = key + "-7";

    QHBoxLayout* chartSetLayout = new QHBoxLayout;

    QStringList barLabels;
    barLabels<<"腿"<< "手"<< "配合"<< "蹬边滑行"<<"海豚腿";

    QVector<QBarSet*> barSet_Vec_5;
    QBarSeries *series_5 = new QBarSeries();
    series_5->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
    series_5->setLabelsFormat("@value");
    series_5->setLabelsVisible(true);
    series_5->setBarWidth(1);
    for(int j=0; j<barLabels.size(); j++){
        QBarSet* barSet = new QBarSet(barLabels.at(j));
        *barSet << 0<<0<<0<<0;
        barSet->setLabelColor(Qt::black);
        series_5->append(barSet);
        barSet_Vec_5.push_back(barSet);
    }

    // 7
    QVector<QBarSet*> barSet_Vec_7;
    QBarSeries *series_7 = new QBarSeries();
    series_7->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
    series_7->setLabelsFormat("@value");
    series_7->setLabelsVisible(true);
    series_7->setBarWidth(1);
    for(int j=0; j<barLabels.size(); j++){
        QBarSet* barSet = new QBarSet(barLabels.at(j));
        *barSet << 0<<0<<0<<0;
        barSet->setLabelColor(Qt::black);
        series_7->append(barSet);
        barSet_Vec_7.push_back(barSet);
    }

    m_all_barSeries_Vec.insert(key_5,series_5);

    // 5
    QChart *chart_5 = new QChart();
    QChartView* barView_5 = new QChartView();
    chart_5->addSeries(series_5);
    chart_5->setTitle(QString("%1不同泳姿项最大力柱状图").arg(key_5));
    chart_5->setAnimationOptions(QChart::AllAnimations);

    // 7
    QChart *chart_7 = new QChart();
    QChartView* barView_7 = new QChartView();
    chart_7->addSeries(series_7);
    chart_7->setTitle(QString("%1不同泳姿项最大力柱状图").arg(key_7));
    chart_7->setAnimationOptions(QChart::AllAnimations);

    // 5
    QStringList categories_5;
    categories_5 << "仰泳" << "蛙泳" << "蝶泳" << "自由泳";
    QBarCategoryAxis *axisX_5 = new QBarCategoryAxis();
    axisX_5->append(categories_5);
    QValueAxis* axisY_5 = new QValueAxis;
    axisY_5->setRange(0,100);
    chart_5->addAxis(axisX_5, Qt::AlignBottom);
    chart_5->addAxis(axisY_5,Qt::AlignLeft);
    series_5->attachAxis(axisY_5);

    chart_5->legend()->setVisible(true);
    chart_5->legend()->setAlignment(Qt::AlignTop);

    barView_5->setChart(chart_5);
    barView_5->setFixedHeight(300);


    // 7
    QStringList categories_7;
    categories_7 << "仰泳" << "蛙泳" << "蝶泳" << "自由泳";
    QBarCategoryAxis *axisX_7 = new QBarCategoryAxis();
    axisX_7->append(categories_7);
    QValueAxis* axisY_7 = new QValueAxis;
    axisY_7->setRange(0,100);
    chart_7->addAxis(axisX_7, Qt::AlignBottom);
    chart_7->addAxis(axisY_7,Qt::AlignLeft);
    series_7->attachAxis(axisY_7);

    chart_7->legend()->setVisible(true);
    chart_7->legend()->setAlignment(Qt::AlignTop);

    barView_7->setChart(chart_7);
    barView_7->setFixedHeight(300);


    int rowSerial=m_all_barSeries_Vec.size() / 1;

    chartSetLayout->addWidget(barView_5);
    chartSetLayout->addWidget(barView_7);
    m_all_ChartLayouts.insert(key,chartSetLayout);
    ui->gridLayout->addLayout(chartSetLayout,rowSerial - 1,0);

    m_all_barSet_Vec.insert(key_5,barSet_Vec_5);
    m_all_barSet_Vec.insert(key_7,barSet_Vec_7);
}


void ComputedPage::updatePersonStatistics(QMap<QString,QVector<int>> personStatistics)
{
    m_axisY->setMax(personStatistics["总人数"].at(0));

    for(int i=0; i<personStatistics["总人数"].size(); i++){
        qDebug() << personStatistics["总人数"].at(i);
        m_set0->replace(i, personStatistics["总人数"].at(i));;
    }
    for(int i=0; i<personStatistics["自由泳"].size(); i++){
        qDebug() << personStatistics["自由泳"].at(i);
        m_set1->replace(i, personStatistics["自由泳"].at(i));
    }
    for(int i=0; i<personStatistics["仰泳"].size(); i++){
        qDebug() << personStatistics["仰泳"].at(i);
        m_set2->replace(i, personStatistics["仰泳"].at(i));
    }
    for(int i=0; i<personStatistics["蛙泳"].size(); i++){
        qDebug() << personStatistics["蛙泳"].at(i);
        m_set3->replace(i, personStatistics["蛙泳"].at(i));
    }
    for(int i=0; i<personStatistics["蝶泳"].size(); i++){
        qDebug() << personStatistics["蝶泳"].at(i);
        m_set4->replace(i, personStatistics["蝶泳"].at(i));
    }
}

void ComputedPage::updateSinglePersonStatistics(QMap<QString,QMap<QString,QVector<QVector<double>>>> result)
{
    QMap<QString,QMap<QString,QVector<QVector<double>>>>::Iterator iter;
    for(iter=result.begin();iter!=result.end();iter++){
        for(int i=0; i<m_all_barSet_Vec[iter.key() + "-5"].size();i++){
            for(int j=0; j<iter.value()["5"].at(i).size(); j++){
                qDebug() << iter.key() + "-5";
                m_all_barSet_Vec[iter.key() + "-5"].at(i)->replace(j,iter.value()["5"].at(i).at(j));
                m_all_barSet_Vec[iter.key() + "-7"].at(i)->replace(j,iter.value()["7"].at(i).at(j));
            }
        }
    }
}


void ComputedPage::deleteSinglePersonChart(QString key)
{
    QString key_5 = key + "-5";
    QString key_7 = key + "-7";
    QHBoxLayout* hLayout = m_all_ChartLayouts[key];
    ui->gridLayout->takeAt(ui->gridLayout->indexOf(m_all_ChartLayouts[key]));
    m_all_chartView[key]->deleteLater();
    m_all_barSet_Vec.remove(key_5);
    m_all_barSet_Vec.remove(key_7);
    m_all_barSeries_Vec.remove(key_5);
    m_all_barSeries_Vec.remove(key_7);
    hLayout->deleteLater();

    ui->gridLayout->update();
}

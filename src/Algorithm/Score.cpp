#include "Score.h"
#include <QDebug>

static Score* INSTANCE=nullptr;
QMap<QString,QMap<QString,QVector<QString>>> Score::m_manScoreCommonMode =
{
    {"自由泳",{{"自腿",{}},{"自手",{}},{"自配合",{}},{"蹬边滑行",{}}}},
    {"仰泳",{{"仰腿",{}},{"仰手",{}},{"仰配合",{}},{"海豚腿(仰卧)",{}},{"蹬边滑行",{}}}},
    {"蛙泳",{{"蛙腿",{}},{"蛙手",{}},{"蛙配合",{}},{"蹬边滑行",{}}}},
    {"蝶泳",{{"蝶腿",{}},{"蝶手",{}},{"蝶配合",{}},{"海豚腿(俯卧)",{}},{"蹬边滑行",{}}}}
};
QMap<QString,QMap<QString,QVector<QString>>> Score::m_womanScoreCommonMode =
{
    {"自由泳",{{"自腿",{}},{"自手",{}},{"自配合",{}},{"蹬边滑行",{}}}},
    {"仰泳",{{"仰腿",{}},{"仰手",{}},{"仰配合",{}},{"海豚腿(仰卧)",{}},{"蹬边滑行",{}}}},
    {"蛙泳",{{"蛙腿",{}},{"蛙手",{}},{"蛙配合",{}},{"蹬边滑行",{}}}},
    {"蝶泳",{{"蝶腿",{}},{"蝶手",{}},{"蝶配合",{}},{"海豚腿(俯卧)",{}},{"蹬边滑行",{}}}}
};
Score::Score(){}


Score *Score::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new Score();
    }
    return INSTANCE;
}
void Score::setScoreTeamStandard(QMap<QString,TableData*> tableDatas)
{
    m_manScoreTeamMode.clear();
    m_womanScoreTeamMode.clear();
    QMap<QString,QMap<QString,QMap<QString,QVector<double>>>>::Iterator iter;
    QList<QString> persons = tableDatas.keys();
    QList<TableData*> records = tableDatas.values();

    for(int i=0; i<persons.length();i++){
        QString gender = persons.at(i).split("-").at(1);
        for(iter=defaultMode.begin();iter!=defaultMode.end();iter++){
            QMap<QString,QMap<QString,QVector<double>>>::Iterator strokeItem_iter;
            for(strokeItem_iter=iter.value().begin(); strokeItem_iter!=iter.value().end(); strokeItem_iter++){
                if(gender == "男"){
                    m_manScoreTeamMode[iter.key()][strokeItem_iter.key()]["5"].push_back(records.at(i)->Values(iter.key(),strokeItem_iter.key(),"5").at(3));
                    m_manScoreTeamMode[iter.key()][strokeItem_iter.key()]["7"].push_back(records.at(i)->Values(iter.key(),strokeItem_iter.key(),"7").at(3));
                }
                if(gender == "女"){
                    m_womanScoreTeamMode[iter.key()][strokeItem_iter.key()]["5"].push_back(records.at(i)->Values(iter.key(),strokeItem_iter.key(),"5").at(3));
                    m_womanScoreTeamMode[iter.key()][strokeItem_iter.key()]["7"].push_back(records.at(i)->Values(iter.key(),strokeItem_iter.key(),"7").at(3));
                }
            }
        }
    }

    for(iter=defaultMode.begin();iter!=defaultMode.end();iter++){
        QMap<QString,QMap<QString,QVector<double>>>::Iterator strokeItem_iter;
        for(strokeItem_iter=iter.value().begin(); strokeItem_iter!=iter.value().end(); strokeItem_iter++){
              sort(m_manScoreTeamMode[iter.key()][strokeItem_iter.key()]["5"].rbegin(),m_manScoreTeamMode[iter.key()][strokeItem_iter.key()]["5"].rend());
              sort(m_manScoreTeamMode[iter.key()][strokeItem_iter.key()]["7"].rbegin(),m_manScoreTeamMode[iter.key()][strokeItem_iter.key()]["7"].rend());
              sort(m_womanScoreTeamMode[iter.key()][strokeItem_iter.key()]["5"].rbegin(),m_womanScoreTeamMode[iter.key()][strokeItem_iter.key()]["5"].rend());
              sort(m_womanScoreTeamMode[iter.key()][strokeItem_iter.key()]["7"].rbegin(),m_womanScoreTeamMode[iter.key()][strokeItem_iter.key()]["7"].rend());
        }
    }
}

QString Score::teamModelScore(QString gender, QString stroke, QString strokeItem, QString distance, QString maxPower)
{
    QVector<QString> convertData;
    QVector<double> datas;
    if(gender=="男"){
        datas = m_manScoreTeamMode[stroke][strokeItem][distance];
    }
    if(gender=="女"){
        datas = m_womanScoreTeamMode[stroke][strokeItem][distance];
    }

    for(int i=0; i<datas.length(); i++){
        convertData.push_back(QString::number(datas.at(i)));
    }
    qDebug() << convertData;
    int index = convertData.indexOf(maxPower);
    if(index==0){
        return QString::number(20);
    }
    if(index==1){
        return QString::number(18);
    }
    if(index==2){
        return QString::number(16);
    }
    if(index>16){
        return 0;
    }
    return QString::number(17- index);
}

void Score::setScoreCommonStandard(QVector<QVector<QString>> scoreDatas)
{
    int rowCount = scoreDatas.length();
    int columnCount = scoreDatas.at(scoreDatas.length()-1).length();
    int strokeIndex=1;
    int strokeItemIndex=2;
    for(int i=0;i<columnCount + 2;++i){
        if(i==0){

        }
        if(i>=1){
            QVector<QString> man_values_vec;
            QVector<QString> woman_values_vec;
            QVector<QString>  woman_slide_value_vec;
            QVector<QString>  man_slide_value_vec;
            if(i<13){
                QString stroke = scoreDatas.at(0).at(strokeIndex);
                QString strokeItem = scoreDatas.at(0).at(strokeItemIndex);
                for(int j=2; j<rowCount; ++j){
                    if(j<rowCount-1){
                        QString woman_value = scoreDatas.at(rowCount-j + 1).at(strokeItemIndex) + "-" + scoreDatas.at(rowCount-j).at(strokeItemIndex);
                        QString woman_slide_value = scoreDatas.at(rowCount-j + 1).at(26) + "-" + scoreDatas.at(rowCount-j).at(26);
                        woman_slide_value_vec.push_back(woman_slide_value);
                        woman_values_vec.push_back(woman_value);

                        QString man_value = scoreDatas.at(rowCount-j + 1).at(strokeIndex) + "-" +scoreDatas.at(rowCount-j).at(strokeIndex);
                        QString man_slide_value = scoreDatas.at(rowCount-j + 1).at(25) + "-" + scoreDatas.at(rowCount-j).at(25);
                        man_slide_value_vec.push_back(man_slide_value);
                        man_values_vec.push_back(man_value);
                    }
                }

                m_manScoreCommonMode[stroke][strokeItem] = man_values_vec;

                m_womanScoreCommonMode[stroke][strokeItem] = woman_values_vec;

                m_manScoreCommonMode[stroke]["蹬边滑行"] = man_slide_value_vec;

                m_womanScoreCommonMode[stroke]["蹬边滑行"] = woman_slide_value_vec;

                strokeIndex = strokeIndex + 2;
                strokeItemIndex = strokeItemIndex + 2;
            }
        }
    }
}

QString Score::commonModeScore(QString gender, QString stroke, QString strokeItem,QString maxPower)
{
    const float EPSINON = 0.00001;
    QVector<int> score = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,18,20};
    float maxPower_f = maxPower.toFloat();
    int scoreResult = 0;
     QVector<QString> scoreVector;
    if(gender == "男"){
        scoreVector = m_manScoreCommonMode[stroke][strokeItem];
    }
    if (gender == "女"){
        scoreVector = m_womanScoreCommonMode[stroke][strokeItem];
    }
    for(int i=0; i< scoreVector.size(); i++){
        float minValue = scoreVector.at(i).split("-").at(0).toFloat();
        float maxValue = scoreVector.at(i).split("-").at(1).toFloat();
        if(maxPower_f > scoreVector.at(scoreVector.size()-1).split("-").at(1).toFloat()){
            qDebug() << "score1" << scoreVector.size();
            scoreResult = score.at(scoreVector.size() + 1);
            return QString::number(scoreResult);
        }
        if(maxPower_f < scoreVector.at(0).split("-").at(0).toFloat()){

            return QString::number(scoreResult);
        }
        if((minValue<maxPower_f && maxPower_f < maxValue) || fabs(maxPower_f-minValue) <= EPSINON){
            return QString::number(score.at(i));
        }
    }
    return QString::number( scoreResult);
}


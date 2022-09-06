﻿#include "TableData.h"

TableData::TableData(QString person,QString stroke,QString strokeItem,QString distance,QVector<double> values)
{
    if(!m_strokes.contains(stroke)){
        m_strokes.push_back(stroke);
    }
    if(!m_strokeItems[stroke].contains(strokeItem)){
        m_strokeItems[stroke].push_back(strokeItem);
    }
    m_person = person;
    m_data[stroke][strokeItem][distance]=values;
}

QString TableData::Person()
{
    return m_person;
}

QVector<double> TableData::Values(QString stroke, QString strokeItem, QString distance)
{
    return m_data[stroke][strokeItem][distance];
}

void TableData::setValues(QString stroke, QString strokeItem, QString distance, QVector<double> values)
{
    if(!m_strokes.contains(stroke)){
        m_strokes.push_back(stroke);
    }
    if(!m_strokeItems[stroke].contains(strokeItem)){
        m_strokeItems[stroke].push_back(strokeItem);
    }
    m_data[stroke][strokeItem][distance] = values;
}

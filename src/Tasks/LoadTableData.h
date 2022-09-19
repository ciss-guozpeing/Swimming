#ifndef LOADTABLEDATA_H
#define LOADTABLEDATA_H


#include <QObject>
#include <QRunnable>

class LoadTableDataRunable : public QObject, public QRunnable
{
    Q_OBJECT

public:
    explicit LoadTableDataRunable(QObject *parent = nullptr);
    static QVector<QStringList> m_tableDatas;
protected:
    void run();

signals:
    void createPersonChart(QString person);
    void createRecordDB(QStringList record);

public slots:
    void receviedTableDatas(QVector<QStringList> tableDatas);
};
#endif // LOADTABLEDATA_H

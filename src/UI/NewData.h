#ifndef NEWDATA_H
#define NEWDATA_H

#include <QObject>
#include <QStandardItem>
#include <QDialog>
#include <QList>
#include <QDateTime>
#include <QPushButton>

namespace Ui {
class NewData;
}

class NewData : public QDialog
{
    Q_OBJECT

private:
    QString m_uniqueData;
    QString dataFormat();
    QString getAge(QString birthdayDate);
    QString getGender(bool isManChecked, bool isWomanChecked);
    QString getCurDate(QDate curDate);

    void _setStroke() const;
    void _setSportLevel() const;
    void _setEnv() const;
    void _setTestDintance() const;
    void _setTeam() const;
    void _setTrainStage() const;



public:
    explicit NewData(QWidget *parent = nullptr);
    ~NewData();
    static NewData *getInstance();

    const QList<QStandardItem*> getRowData(int historyRowCount);
    bool isRequired(QList<QStandardItem*> aItemList);
    void setWarnText(QString text);
    void clearWarnText();
    QString uniqueData();

private slots:
    void on_restStorkeType(const QString &text);

private:
    Ui::NewData *ui;
};

#endif // NEWDATA_H

#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H
#include <QPushButton>
#include <QDialog>

namespace Ui {
class AccountManager;
}

class AccountManager : public QDialog
{
    Q_OBJECT
    bool m_isApply = false;
public:
    explicit AccountManager(QWidget *parent = nullptr);
    ~AccountManager();
    static AccountManager *getInstance();

    void setIsApply(bool isApply);
    bool isApply();
private slots:

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::AccountManager *ui;
};

#endif // ACCOUNTMANAGER_H

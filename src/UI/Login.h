#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT
    QString password;
    bool m_userType;
    QString m_lastLoginUser;

public:
    static Login* getInstance();
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    bool userType();
    void setUserType(bool userType);

    QString lastLoginUser();
    void setLastLoginUser(QString lastLoginUser);

    void clearPassword();
signals:
    void loginOnclicked(QString text, bool userType);
    void showMainWindow();

private slots:
    void on_loginButton_clicked();

    void on_label_linkActivated(const QString &link);

    void on_label_linkHovered(const QString &link);

private:
    Ui::Login *ui;
};

#endif // LOGIN_H

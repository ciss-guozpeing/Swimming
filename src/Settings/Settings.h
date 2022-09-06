#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();
    static Settings *getInstance();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H

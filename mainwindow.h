#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMap>
#include <QList>
#include <QString>
#include <QMainWindow>
#include <QCloseEvent>
#include <QStackedLayout>
#include <QPixmap>
#include <QPushButton>
#include <QDesktopWidget>

#include "src/UI/ClusterPage.h"
#include "src/Excel/Player.h"
#include "src/UI/TableView.h"
#include "src/UI/NewData.h"
#include "src/UI/Visualization/VisualizationPage.h"
#include "src/Settings/TableSetting.h"
#include "src/Settings/Settings.h"
#include "src/Settings/User/AccountManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    enum SCOREMODE{
        Team,
        Common
    };
    int m_scoreMode;
    QLabel* m_username;
    QPixmap m_userPixmap;
    QPushButton* m_profileBtn;
    QAction* m_actProfile;
    QAction* m_actAccount;
    QAction* m_actQuit;
    TableModelManager* m_tableModelManager;
    QString m_nameSearch;
    void setToolBarStatus();
    void initUI();
    TableSetting* tableSetting();
    TableView* tableView();
    Player* Player();
    Settings* Settings();
    VisualizationPage* VisualizationPage();
signals:
    void sendTableDatas(QVector<QStringList> tableDatas);

private slots:
    void on_actAbout_triggered();

    void on_actHistData_triggered();

    void on_actSetting_triggered();

    void on_actMain_triggered();

    void on_mainSetting_clicked();

    void on_mainComputedBtn_clicked();

    void on_mainClusterBtn_clicked();

    void on_mainStatisticsBtn_clicked();

    void on_mainAsSaveBtn_clicked();

    void on_mainOpenExcelBtn_clicked();

    void on_mainTemplateBtn_clicked();

    void on_mainViewBtn_clicked();

    void on_mainExportBtn_clicked();

    void on_mainAllDeleteBtn_clicked();

    void on_appendData_clicked();

    void on_mainSearch_clicked();

    void on_mainRefresh_clicked();

    void on_actVisualization_triggered();

    void actQuite_triggered();

    void actAccount_triggered();

    void on_scorePushButton_clicked();

    void restStorkeType(const QString& text);

    void setKValue();

    void setUserName(QString text, bool userType);

    void nameSearch(QString text);

protected:
    void closeEvent(QCloseEvent* event);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

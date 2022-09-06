#ifndef VIEWPAGE_H
#define VIEWPAGE_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class ViewPage;
}

class ViewPage : public QDialog
{
    Q_OBJECT
    QWidget* createSingleShowMessage();
    static QVector<QWidget*> m_showWidgets;
public:
    explicit ViewPage(QWidget *parent = nullptr);
    ~ViewPage();
    static ViewPage *getInstance();

    void createShowMessage(QVector<int> rowIndexs);

private:
    Ui::ViewPage *ui;
};

#endif // VIEWPAGE_H

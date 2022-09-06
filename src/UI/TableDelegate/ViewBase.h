#ifndef VIEWBASE_H
#define VIEWBASE_H

#include <QWidget>

namespace Ui {
class ViewBase;
}

class ViewBase : public QWidget
{
    Q_OBJECT

public:
    explicit ViewBase(QWidget *parent = nullptr);
    ~ViewBase();
    void setText(QVector<QString> rowData);
private:
    Ui::ViewBase *ui;
};

#endif // VIEWBASE_H

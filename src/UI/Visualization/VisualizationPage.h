#ifndef VISUALIZATIONPAGE_H
#define VISUALIZATIONPAGE_H

#include <QWidget>

namespace Ui {
class VisualizationPage;
}

class VisualizationPage : public QWidget
{
    Q_OBJECT

public:
    explicit VisualizationPage(QWidget *parent = nullptr);
    ~VisualizationPage();
    static VisualizationPage *getInstance();
private:
    Ui::VisualizationPage *ui;
};

#endif // VISUALIZATIONPAGE_H

#include "VisualizationPage.h"
#include "ui_VisualizationPage.h"

static VisualizationPage* INSTANCE=nullptr;
VisualizationPage::VisualizationPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisualizationPage)
{
    ui->setupUi(this);
}

VisualizationPage::~VisualizationPage()
{
    delete ui;
}

VisualizationPage *VisualizationPage::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new VisualizationPage();
    }
    return INSTANCE;
}

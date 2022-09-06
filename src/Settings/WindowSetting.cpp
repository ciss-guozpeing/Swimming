#include "WindowSetting.h"
#include <QDebug>
static WindowSetting* INSTANCE=nullptr;

WindowSetting::WindowSetting()
{
    m_windowSetting = new QSettings(qApp->organizationName(),qApp->applicationName());
}

WindowSetting::~WindowSetting()
{
    delete this;
}

WindowSetting *WindowSetting::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new WindowSetting();
    }
    return INSTANCE;
}

void WindowSetting::setSupperUser()
{
    m_windowSetting->setValue("supperUser",true);
}

bool WindowSetting::isExistsSupperUser()
{
    bool isExists = m_windowSetting->value("supperUser").toBool();
    return  isExists;
}

void WindowSetting::configureDarkUi() {
  qApp->setStyle(QStyleFactory::create("Fusion"));

  // clang-format off
    QPalette palette;
    palette.setColor(QPalette::Base,            QColor("#21373f"));
    palette.setColor(QPalette::Link,            QColor("#409da0"));
    palette.setColor(QPalette::Button,          QColor("#21373f"));
    palette.setColor(QPalette::Window,          QColor("#21373f"));
    palette.setColor(QPalette::Text,            QColor("#ffffff"));
    palette.setColor(QPalette::Midlight,        QColor("#0e1419"));
    palette.setColor(QPalette::Highlight,       QColor("#409da0"));
    palette.setColor(QPalette::BrightText,      QColor("#ffffff"));
    palette.setColor(QPalette::ButtonText,      QColor("#ffffff"));
    palette.setColor(QPalette::WindowText,      QColor("#ffffff"));
    palette.setColor(QPalette::ToolTipBase,     QColor("#e6e0b2"));
    palette.setColor(QPalette::ToolTipText,     QColor("#e6e0b2"));
    palette.setColor(QPalette::HighlightedText, QColor("#e6e0b2"));
    qApp->setPalette(palette);
  // clang-format on
}

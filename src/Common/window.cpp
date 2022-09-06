#include "window.h"
static Window* INSTANCE = nullptr;

Window::Window(QMainWindow *parent)
    : QObject{parent}
{

}

Window* Window::getInstalce()
{
    if (INSTANCE) {
        INSTANCE = new Window();
    }
    return INSTANCE;
}

QMap<QString,int> Window::getMainWindowSize()
{
}

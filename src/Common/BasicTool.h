#ifndef BASICTOOL_H
#define BASICTOOL_H

#include <QString>
#include <QMetaType>

class BasicTool
{

public:
    BasicTool();
    static BasicTool *getInstance();


    bool isDigitStr(QString str);
};

#endif // BASICTOOL_H

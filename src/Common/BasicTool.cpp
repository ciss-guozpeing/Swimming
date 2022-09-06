#include "basictool.h"

static BasicTool* INSTANCE=nullptr;
BasicTool::BasicTool()
{

}

BasicTool *BasicTool::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new BasicTool();
    }
    return INSTANCE;
}


bool BasicTool::isDigitStr(QString str)
{/***
  *判断一个字符串是否为纯数字
  */
    QByteArray ba = str.toLatin1();//QString 转换为 char*
     const char *s = ba.data();

    while(*s && *s>='0' && *s<='9') s++;

    if (*s)
    { //不是纯数字
        return false;
    }
    else
    { //纯数字
        return true;
    }
}

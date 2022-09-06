#include "Message.h"
#include "../AppInfo.h"
#include <QPushButton>
#include <QDialogButtonBox>
static ErrMessage* ErrINSTANCE = nullptr;
static WarnMessage* WarnINSTANCE = nullptr;
static InfoMessage* InfoINSTANCE = nullptr;
static QuestionMessage* QuestionINSTANCE = nullptr;
Message::Message() {
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);
    this->setWindowIcon(QIcon(":/images/images/swimming.png"));
    this->setFixedSize(200,200);
//    this->button(QMessageBox::Yes)->setText("是");
//    this->button(QMessageBox::No)->setText("否");
//    this->button(QMessageBox::Cancel)->setText("取消");
}

ErrMessage *ErrMessage::getInstance()
{
    if (!ErrINSTANCE) {
        ErrINSTANCE = new ErrMessage();
    }
    return ErrINSTANCE;
}

ErrMessage::ErrMessage() {
    this->setIcon(QMessageBox::Critical);
}

int ErrMessage::sendMessage(const QString &title, const QString &text)
{
    int ret = QMessageBox::critical(this, title, text,
                                    QMessageBox::Ok,
                                    QMessageBox::Ok);
    return ret;
}

WarnMessage *WarnMessage::getInstance()
{
    if (!WarnINSTANCE) {
        WarnINSTANCE = new WarnMessage();
    }
    return WarnINSTANCE;
}

WarnMessage::WarnMessage() {
    this->setIcon(QMessageBox::Information);
}

int WarnMessage::sendMessage(const QString &title, const QString &text)
{
    int ret = QMessageBox::warning(this, title, text,
                                   QMessageBox::Cancel | QMessageBox::No| QMessageBox::Yes,
                                   QMessageBox::No);

    return ret;
}

InfoMessage* InfoMessage::getInstance()
{
    if(!InfoINSTANCE) {
        InfoINSTANCE = new InfoMessage();
    }
    return InfoINSTANCE;
}

InfoMessage::InfoMessage()
{
    this->setIcon(QMessageBox::Information);
}

int InfoMessage::sendMessage(const QString &title, const QString &text)
{
    int ret = QMessageBox::information(this, title, text,
                                       QMessageBox::Ok,
                                       QMessageBox::Ok);
    return ret;
}

QuestionMessage* QuestionMessage::getInstance()
{
    if (!QuestionINSTANCE) {
        QuestionINSTANCE = new QuestionMessage();
    }
    return QuestionINSTANCE;
}

QuestionMessage::QuestionMessage()
{
    this->setIcon(QMessageBox::Question);
}

int QuestionMessage::sendMessage(const QString &title, const QString &text)
{
    int ret = QMessageBox::question(this, title, text,
                                    QMessageBox::Cancel | QMessageBox::Close | QMessageBox::Ok,
                                    QMessageBox::Close);
    return ret;
}

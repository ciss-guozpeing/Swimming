#include "ModuleManager.h"

static ModuleManager* INSTANCE =nullptr;

ModuleManager::ModuleManager() {}

ModuleManager *ModuleManager::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new ModuleManager();
    }
    return INSTANCE;
}

void ModuleManager::initModuleInstance()
{//实现单例模式
    m_player = Player::getInstance();
    auto basictool = BasicTool::getInstance();
    auto statistics = Statistics::getInstance();
    auto errMessage = ErrMessage::getInstance();
    auto warnMessage = WarnMessage::getInstance();
    auto infoMessage = InfoMessage::getInstance();
    auto questionMessage = QuestionMessage::getInstance();
    m_tableSetting = TableSetting::getInstance();
    m_zpNotificationManager = ZpNotificationManager::getInstance();
}

Player* ModuleManager::player()
{
    return m_player;
}

TableSetting* ModuleManager::tableSetting()
{
    return m_tableSetting;
}

ZpNotificationManager* ModuleManager::zpNotificationManager()
{
    return m_zpNotificationManager;
}

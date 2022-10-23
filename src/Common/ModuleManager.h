#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include "src/Excel/Player.h"
#include "src/Common/Basictool.h"
#include "src/Common/Message.h"
#include "src/Common/Notice/Notification/ZpNotificationManager.h"
#include "src/Algorithm/kmeans.h"
#include "src/Algorithm/statistics.h"
#include "src/Settings/TableSetting.h"
#include "src/Settings/WindowSetting.h"


class ModuleManager
{
    ZpNotificationManager* m_zpNotificationManager;
    TableSetting* m_tableSetting;
    Player* m_player;

public:
    ModuleManager();
    static ModuleManager* getInstance();
    void initModuleInstance();

    Player* player();
    TableSetting* tableSetting();
    ZpNotificationManager* zpNotificationManager();
};

#endif // MODULEMANAGER_H

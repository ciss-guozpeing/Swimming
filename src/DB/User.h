#ifndef USER_H
#define USER_H

#include "BaseDB.h"
namespace DB{
    class User: public Base
    {
    public:
        User();
        bool isExistsUser(QString username, QString password);
        bool isSupperUser(QString username, QString password);

        void createDefaultSupperUser();
        void createSupperUser(QString username, QString password);
        void createUser(QString username, QString password);
        void updateUser(QString old_username, QString old_password, QString new_username, QString new_password);

    };
}


#endif // USER_H

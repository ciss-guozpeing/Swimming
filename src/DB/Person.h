#ifndef PERSON_H
#define PERSON_H

#include "BaseDB.h"
#include "src/Common/ReturnData.h"
namespace DB{
    class Person : public Base
    {
        bool _isExistsPerson(QString name, QString birthday, QString gender, QString weight);
    public:
        explicit Person();
        ReturnData isExistsPerson(QString name, QString gender, QString birthday,QString weight);

        ReturnData createPerson(QString name, QString birthday, QString gender, QString weight);
        void updatePerson(QString name, QString gender, QString birthday, QString weight);
        void deletePerson(QString id); // TODO

        void updateName(QString id, QString name);
        void updateBirthday(QString id, QString birthday);
        void updateGender(QString id, QString gender);
        void updateWeight(QString id, QString weight);


    signals:

    };
}


#endif // PERSON_H

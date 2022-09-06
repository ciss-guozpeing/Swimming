#ifndef PERSON_H
#define PERSON_H

#include "BaseDB.h"

namespace DB{
    class Person : public Base
    {
        bool _isExistsPerson(QString name, QString birthday, QString gender);
    public:
        explicit Person();
        void createPerson(QString name, QString birthday, QString gender, QString weight);
    signals:

    };
}


#endif // PERSON_H

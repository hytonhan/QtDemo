#include "teacher.h"

Teacher::Teacher(QString firstName, QString lastName, QString address, QString phoneNumber, QString id, float salary, QString field)
    :Worker(firstName, lastName, address, phoneNumber, id, salary)
    , field_(field)
{
}

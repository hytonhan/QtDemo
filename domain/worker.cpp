#include <QString>
#include "worker.h"

Worker::Worker(QString firstName, QString lastName, QString address, QString phoneNumber, QString id, float salary)
    : Person(firstName, lastName, address, phoneNumber, id)
    , salary_(salary)
{
}

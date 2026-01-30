#include <QString>
#include "worker.h"

Worker::Worker(const QString& firstName,
               const QString& lastName,
               const QString& address,
               const QString& phoneNumber,
               const QString& id,
               float salary)
    : Person(firstName, lastName, address, phoneNumber, id)
    , salary_(salary)
{
}

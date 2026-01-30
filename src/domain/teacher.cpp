#include "teacher.h"

Teacher::Teacher(const QString& firstName,
                 const QString& lastName,
                 const QString& address,
                 const QString& phoneNumber,
                 const QString& id,
                 const float salary,
                 const QString& field)
    :Worker(firstName, lastName, address, phoneNumber, id, salary)
    , field_(field)
{
}

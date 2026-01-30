#include "student.h"

Student::Student(const QString& firstName,
                 const QString& lastName,
                 const QString& address,
                 const QString& phoneNumber,
                 const QString& id)
    : Person(firstName, lastName, address, phoneNumber, id)
{
}

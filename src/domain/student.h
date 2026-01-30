#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"

class Student :
    public Person
{
public:
    Student(const QString& firstName,
            const QString& lastName,
            const QString& address,
            const QString& phoneNumber,
            const QString& id);
};

#endif // STUDENT_H

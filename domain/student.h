#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"

class Student :
    public Person
{
public:
    Student(QString firstName, QString lastName, QString address, QString phoneNumber, QString id);
};

#endif // STUDENT_H

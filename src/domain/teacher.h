#ifndef TEACHER_H
#define TEACHER_H

#include <QString>
#include "worker.h"

class Teacher:
    public Worker
{
protected:
    QString field_;
public:
    Teacher(QString firstName, QString lastName, QString address, QString phoneNumber, QString id, float salary, QString field);

    QString field() const { return field_; }
};

#endif // TEACHER_H

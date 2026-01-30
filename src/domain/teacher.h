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
    Teacher(const QString& firstName,
            const QString& lastName,
            const QString& address,
            const QString& phoneNumber,
            const QString& id,
            const float salary,
            const QString& field);

    QString field() const { return field_; }
};

#endif // TEACHER_H

#ifndef WORKER_H
#define WORKER_H

#include "person.h"

class Worker :
    public Person
{
protected:
    float salary_;
public:
    Worker(QString firstName, QString lastName, QString address, QString phoneNumber, QString id, float salary);

    float salary() const { return salary_; }
};

#endif // WORKER_H

#ifndef WORKER_H
#define WORKER_H

#include "person.h"

class Worker :
    public Person
{
protected:
    float salary_;
public:
    Worker(const QString& firstName,
           const QString& lastName,
           const QString& address,
           const QString& phoneNumber,
           const QString& id,
           const float salary);

    float salary() const { return salary_; }
};

#endif // WORKER_H

#ifndef PERSON_H
#define PERSON_H
#include <QString>

class Person
{
protected:
    QString firstName_;
    QString address_;
    QString phoneNumber_;
    QString lastName_;
    QString id_;
public:
    Person(QString firstName, QString lastName, QString address, QString phoneNumber, QString id);
    QString firstName() const { return firstName_; }
    QString lastName() const { return lastName_; }
    QString fullName() const { return firstName_ + " " + lastName_; }
    QString address() const { return address_; }
    QString phoneNumber() const { return phoneNumber_; }
    QString id() const { return id_; }
};

#endif // PERSON_H

#ifndef PERSON_H
#define PERSON_H
#include <QString>

class Person
{
protected:
    QString firstName_;
    QString lastName_;
    QString address_;
    QString phoneNumber_;
    QString id_;
public:
    Person(const QString& firstName,
           const QString& lastName,
           const QString& address,
           const QString& phoneNumber,
           const QString& id);
    QString firstName() const { return firstName_; }
    QString lastName() const { return lastName_; }
    QString fullName() const { return firstName_ + " " + lastName_; }
    QString address() const { return address_; }
    QString phoneNumber() const { return phoneNumber_; }
    QString id() const { return id_; }
};

#endif // PERSON_H

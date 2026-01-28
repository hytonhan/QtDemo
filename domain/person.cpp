#include "person.h"

Person::Person(QString firstName, QString lastName, QString address, QString phoneNumber, QString id)
    : firstName_(firstName)
    , lastName_(lastName)
    , address_(address)
    , phoneNumber_(phoneNumber)
    , id_(id)
{}

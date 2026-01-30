#include "person.h"

Person::Person(const QString& firstName,
               const QString& lastName,
               const QString& address,
               const QString& phoneNumber,
               const QString& id)
    : firstName_(firstName)
    , lastName_(lastName)
    , address_(address)
    , phoneNumber_(phoneNumber)
    , id_(id)
{}

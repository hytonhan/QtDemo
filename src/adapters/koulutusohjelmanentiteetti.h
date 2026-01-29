#ifndef KOULUTUSOHJELMANENTITEETTI_H
#define KOULUTUSOHJELMANENTITEETTI_H

#pragma once

#include <QString>

class KoulutusOhjelmanEntiteetti
{
public:
    virtual ~KoulutusOhjelmanEntiteetti() = default;
    virtual int id() const = 0;
    virtual QString displayName() const = 0;
};

#endif // KOULUTUSOHJELMANENTITEETTI_H

#ifndef KOULUTUSOHJELMANENTITEETTIREPOSITORY_H
#define KOULUTUSOHJELMANENTITEETTIREPOSITORY_H

#pragma once

#include <QSqlDatabase>
#include <vector>
#include "../adapters/koulutusohjelmanentiteetti.h"

class KoulutusOhjelmanEntiteettiRepository
{
public:
    explicit KoulutusOhjelmanEntiteettiRepository(QSqlDatabase db);
    virtual ~KoulutusOhjelmanEntiteettiRepository() = default;

    virtual std::vector<std::unique_ptr<KoulutusOhjelmanEntiteetti>> fetchAvailable(int programId) = 0;
    virtual std::vector<std::unique_ptr<KoulutusOhjelmanEntiteetti>> fetchAssigned(int programId) = 0;

    virtual void add(int entityId, int programId) = 0;
    virtual void remove(int entityId, int programId) = 0;

protected:
    QSqlDatabase db_;
};

#endif // KOULUTUSOHJELMANENTITEETTIREPOSITORY_H

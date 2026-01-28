#ifndef OPETTAJAENTITEETTIREPOSITORY_H
#define OPETTAJAENTITEETTIREPOSITORY_H

#include "koulutusohjelmanentiteettirepository.h"
#include "../adapters/koulutusohjelmanentiteetti.h"

class OpettajaEntiteettiRepository : public KoulutusOhjelmanEntiteettiRepository
{
public:
    explicit OpettajaEntiteettiRepository(QSqlDatabase db);
    std::vector<std::unique_ptr<KoulutusOhjelmanEntiteetti>> fetchAvailable(int programId) override;
    std::vector<std::unique_ptr<KoulutusOhjelmanEntiteetti>> fetchAssigned(int programId) override;
    void add(int teacherId, int programId) override;
    void remove(int teacherId, int programId) override;
};

#endif // OPETTAJAENTITEETTIREPOSITORY_H

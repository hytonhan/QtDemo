#ifndef OPISKELIJAENTITEETTIREPOSITORY_H
#define OPISKELIJAENTITEETTIREPOSITORY_H

#include "koulutusohjelmanentiteettirepository.h"
#include "../adapters/koulutusohjelmanentiteetti.h"

class OpiskelijaEntiteettiRepository : public KoulutusOhjelmanEntiteettiRepository
{
public:
    explicit OpiskelijaEntiteettiRepository(QSqlDatabase db);
    std::vector<std::unique_ptr<KoulutusOhjelmanEntiteetti>> fetchAvailable(int programId) override;
    std::vector<std::unique_ptr<KoulutusOhjelmanEntiteetti>> fetchAssigned(int programId) override;
    void add(int studentId, int programId) override;
    void remove(int studentId, int programId) override;
};

#endif // OPISKELIJAENTITEETTIREPOSITORY_H

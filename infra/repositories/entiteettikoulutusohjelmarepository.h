#ifndef ENTITEETTIKOULUTUSOHJELMAREPOSITORY_H
#define ENTITEETTIKOULUTUSOHJELMAREPOSITORY_H

#pragma once

#include <QSqlDatabase>
#include <vector>
#include "../../domain/program.h"

class EntiteettiKoulutusOhjelmaRepository
{
public:
    explicit EntiteettiKoulutusOhjelmaRepository(QSqlDatabase db);
    virtual ~EntiteettiKoulutusOhjelmaRepository() = default;

    virtual std::vector<Program> fetchAssignedPrograms(int entityId) = 0;
    virtual std::vector<Program> fetchAvailablePrograms(int entityId) = 0;

    virtual void addProgram(int entityId, int programId) = 0;
    virtual void removeProgram(int entityId, int programId) = 0;

protected:
    QSqlDatabase db_;
};

#endif // ENTITEETTIKOULUTUSOHJELMAREPOSITORY_H

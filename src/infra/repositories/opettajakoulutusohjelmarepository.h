#ifndef OPETTAJAKOULUTUSOHJELMAREPOSITORY_H
#define OPETTAJAKOULUTUSOHJELMAREPOSITORY_H

#include "entiteettikoulutusohjelmarepository.h"

class OpettajaKoulutusOhjelmaRepository : public EntiteettiKoulutusOhjelmaRepository
{
public:
    explicit OpettajaKoulutusOhjelmaRepository(QSqlDatabase db);

    std::vector<Program> fetchAssignedPrograms(int entityId);
    std::vector<Program> fetchAvailablePrograms(int entityId);

    void addProgram(int entityId, int programId);
    void removeProgram(int entityId, int programId);
};

#endif // OPETTAJAKOULUTUSOHJELMAREPOSITORY_H

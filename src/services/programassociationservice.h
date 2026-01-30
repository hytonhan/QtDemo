#ifndef PROGRAMASSOCIATIONSERVICE_H
#define PROGRAMASSOCIATIONSERVICE_H

#pragma once

#include <QString>
#include "../domain/program.h"

struct AssociationItem
{
    int id;
    QString displayName;
};

class ProgramAssociationService
{
public:
    virtual ~ProgramAssociationService() = default;

    virtual std::vector<AssociationItem> fetchAvailable(int programId) const = 0;
    virtual std::vector<AssociationItem> fetchAssigned(int programId) const = 0;

    virtual std::vector<Program> fetchPrograms(int entityId) const = 0;

    virtual void link(int programId, int entityId) = 0;
    virtual void unlink(int programId, int entityId) = 0;
};

#endif // PROGRAMASSOCIATIONSERVICE_H

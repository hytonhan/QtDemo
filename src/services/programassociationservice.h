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

    virtual std::variant<std::vector<AssociationItem>, QString> fetchAvailable(int programId) const = 0;
    virtual std::variant<std::vector<AssociationItem>, QString> fetchAssigned(int programId) const = 0;
    virtual std::variant<std::vector<Program>, QString> fetchPrograms(int entityId) const = 0;

    virtual std::optional<QString> link(int programId, int entityId) = 0;
    virtual std::optional<QString> unlink(int programId, int entityId) = 0;
};

#endif // PROGRAMASSOCIATIONSERVICE_H

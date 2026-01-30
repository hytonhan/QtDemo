#ifndef PROGRAMSTUDENTASSOCIATIONSERVICE_H
#define PROGRAMSTUDENTASSOCIATIONSERVICE_H

#include "programassociationservice.h"
#include "../infra/repositories/programstudentrepository.h"

class ProgramStudentAssociationService : public ProgramAssociationService
{
public:
    explicit ProgramStudentAssociationService(ProgramStudentRepository& repo);

    std::variant<std::vector<AssociationItem>, QString> fetchAvailable(int programId) const override;
    std::variant<std::vector<AssociationItem>, QString> fetchAssigned(int programId) const override;
    std::variant<std::vector<Program>, QString> fetchPrograms(int studentId) const override;

    std::optional<QString> link(int programId, int studentId) override;
    std::optional<QString> unlink(int programId, int studentId) override;

private:
    ProgramStudentRepository& repo_;
};

#endif // PROGRAMSTUDENTASSOCIATIONSERVICE_H

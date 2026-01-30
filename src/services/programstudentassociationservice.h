#ifndef PROGRAMSTUDENTASSOCIATIONSERVICE_H
#define PROGRAMSTUDENTASSOCIATIONSERVICE_H

#include "programassociationservice.h"
#include "../infra/repositories/programstudentrepository.h"

class ProgramStudentAssociationService : public ProgramAssociationService
{
public:
    explicit ProgramStudentAssociationService(
        ProgramStudentRepository& repo);

    std::vector<AssociationItem> fetchAvailable(int programId) const override;
    std::vector<AssociationItem> fetchAssigned(int programId) const override;
    std::vector<Program> fetchPrograms(int studentId) const override;

    void link(int programId, int studentId) const override;
    void unlink(int programId, int studentId) const override;

private:
    ProgramStudentRepository& repo_;
};

#endif // PROGRAMSTUDENTASSOCIATIONSERVICE_H

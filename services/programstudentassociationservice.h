#ifndef PROGRAMSTUDENTASSOCIATIONSERVICE_H
#define PROGRAMSTUDENTASSOCIATIONSERVICE_H

#include "programassociationservice.h"
#include "../infra/repositories/programstudentrepository.h"

class ProgramStudentAssociationService : public ProgramAssociationService
{
public:
    explicit ProgramStudentAssociationService(
        ProgramStudentRepository& repo);

    std::vector<AssociationItem> fetchAvailable(int programId) override;
    std::vector<AssociationItem> fetchAssigned(int programId) override;
    std::vector<Program> fetchPrograms(int studentId) override;

    void link(int programId, int studentId) override;
    void unlink(int programId, int studentId) override;

private:
    ProgramStudentRepository& repo_;
};

#endif // PROGRAMSTUDENTASSOCIATIONSERVICE_H

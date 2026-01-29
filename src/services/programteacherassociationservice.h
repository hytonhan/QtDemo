#ifndef PROGRAMTEACHERASSOCIATIONSERVICE_H
#define PROGRAMTEACHERASSOCIATIONSERVICE_H

#include "programassociationservice.h"
#include "../infra/repositories/programteacherrepository.h"

class ProgramTeacherAssociationService : public ProgramAssociationService
{
public:
    explicit ProgramTeacherAssociationService(ProgramTeacherRepository& repo);

    std::vector<AssociationItem> fetchAvailable(int programId) override;
    std::vector<AssociationItem> fetchAssigned(int programId) override;
    std::vector<Program> fetchPrograms(int teacherId) override;

    void link(int programId, int teacherId) override;
    void unlink(int programId, int teacherId) override;

private:
    ProgramTeacherRepository& repo_;
};
#endif // PROGRAMTEACHERASSOCIATIONSERVICE_H

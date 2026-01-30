#ifndef PROGRAMTEACHERASSOCIATIONSERVICE_H
#define PROGRAMTEACHERASSOCIATIONSERVICE_H

#include "programassociationservice.h"
#include "../infra/repositories/programteacherrepository.h"

class ProgramTeacherAssociationService : public ProgramAssociationService
{
public:
    explicit ProgramTeacherAssociationService(ProgramTeacherRepository& repo);

    std::vector<AssociationItem> fetchAvailable(int programId) const override;
    std::vector<AssociationItem> fetchAssigned(int programId) const override;
    std::vector<Program> fetchPrograms(int teacherId) const override;

    void link(int programId, int teacherId) const override;
    void unlink(int programId, int teacherId) const override;

private:
    ProgramTeacherRepository& repo_;
};
#endif // PROGRAMTEACHERASSOCIATIONSERVICE_H

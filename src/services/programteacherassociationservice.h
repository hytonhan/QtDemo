#ifndef PROGRAMTEACHERASSOCIATIONSERVICE_H
#define PROGRAMTEACHERASSOCIATIONSERVICE_H

#include "programassociationservice.h"
#include "../infra/repositories/programteacherrepository.h"

class ProgramTeacherAssociationService : public ProgramAssociationService
{
public:
    explicit ProgramTeacherAssociationService(ProgramTeacherRepository& repo);

    std::variant<std::vector<AssociationItem>, QString> fetchAvailable(int programId) const override;
    std::variant<std::vector<AssociationItem>, QString> fetchAssigned(int programId) const override;
    std::variant<std::vector<Program>, QString> fetchPrograms(int teacherId) const override;

    std::optional<QString> link(int programId, int teacherId) override;
    std::optional<QString> unlink(int programId, int teacherId) override;

private:
    ProgramTeacherRepository& repo_;
};
#endif // PROGRAMTEACHERASSOCIATIONSERVICE_H

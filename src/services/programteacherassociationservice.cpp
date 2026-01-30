#include "programteacherassociationservice.h"

ProgramTeacherAssociationService::ProgramTeacherAssociationService(ProgramTeacherRepository& repo)
    : repo_(repo)
{}

std::vector<AssociationItem> ProgramTeacherAssociationService::fetchAvailable(int programId) const
{
    auto teachers = repo_.teachersNotInProgram(programId);
    std::vector<AssociationItem> result;

    for (const auto& t: teachers) {
        result.push_back({
            t.id().toInt(),
            t.fullName()
        });
    }
    return result;
}

std::vector<AssociationItem> ProgramTeacherAssociationService::fetchAssigned(int programId) const
{
    auto teachers = repo_.teachersForProgram(programId);
    std::vector<AssociationItem> result;

    for (const auto& t: teachers) {
        result.push_back({
            t.id().toInt(),
            t.fullName()
        });
    }
    return result;
}

std::vector<Program> ProgramTeacherAssociationService::fetchPrograms(int teacherId) const
{
    auto programs = repo_.programsForTeacher(teacherId);
    std::vector<Program> result;

    for (const auto& t: programs) {
        result.push_back({
            t.id(),
            t.name()
        });
    }
    return result;
}

void ProgramTeacherAssociationService::link(int programId, int teacherId) const
{
    repo_.assignTeacher(programId, teacherId);
}

void ProgramTeacherAssociationService::unlink(int programId, int teacherId) const
{
    repo_.removeTeacher(programId, teacherId);
}

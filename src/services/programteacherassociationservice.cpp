#include "programteacherassociationservice.h"

ProgramTeacherAssociationService::ProgramTeacherAssociationService(ProgramTeacherRepository& repo)
    : repo_(repo)
{}

std::variant<std::vector<AssociationItem>, QString> ProgramTeacherAssociationService::fetchAvailable(int programId) const
{
    auto teachers = repo_.teachersNotInProgram(programId);

    if (std::holds_alternative<QString>(teachers)) {
        return std::get<QString>(teachers);
    }

    std::vector<AssociationItem> result;
    for (const auto& t: std::get<std::vector<Teacher>>(teachers)) {
        result.push_back({
            t.id().toInt(),
            t.fullName()
        });
    }
    return result;
}

std::variant<std::vector<AssociationItem>, QString> ProgramTeacherAssociationService::fetchAssigned(int programId) const
{
    auto teachers = repo_.teachersForProgram(programId);
    if (std::holds_alternative<QString>(teachers)) {
        return std::get<QString>(teachers);
    }

    std::vector<AssociationItem> result;

    for (const auto& t: std::get<std::vector<Teacher>>(teachers)) {
        result.push_back({
            t.id().toInt(),
            t.fullName()
        });
    }
    return result;
}

std::variant<std::vector<Program>, QString> ProgramTeacherAssociationService::fetchPrograms(int teacherId) const
{
    auto programs = repo_.programsForTeacher(teacherId);
    if (std::holds_alternative<QString>(programs)) {
        return std::get<QString>(programs);
    }
    std::vector<Program> result;

    for (const auto& t: std::get<std::vector<Program>>(programs)) {
        result.push_back({
            t.id(),
            t.name()
        });
    }
    return result;
}

std::optional<QString> ProgramTeacherAssociationService::link(int programId, int teacherId)
{
    return repo_.assignTeacher(programId, teacherId);
}

std::optional<QString> ProgramTeacherAssociationService::unlink(int programId, int teacherId)
{
    return repo_.removeTeacher(programId, teacherId);
}

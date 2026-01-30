#include "programstudentassociationservice.h"

ProgramStudentAssociationService::ProgramStudentAssociationService(ProgramStudentRepository& repo)
    : repo_(repo)
{}

std::variant<std::vector<AssociationItem>, QString> ProgramStudentAssociationService::fetchAvailable(int programId) const
{
    auto students = repo_.studentsNotInProgram(programId);
    if (std::holds_alternative<QString>(students)) {
        return std::get<QString>(students);
    }
    std::vector<AssociationItem> result;

    for (const auto& s: std::get<std::vector<Student>>(students)) {
        result.push_back({
            s.id().toInt(),
            s.fullName()
        });
    }
    return result;
}

std::variant<std::vector<AssociationItem>, QString> ProgramStudentAssociationService::fetchAssigned(int programId) const
{
    auto students = repo_.studentsForProgram(programId);
    if (std::holds_alternative<QString>(students)) {
        return std::get<QString>(students);
    }
    std::vector<AssociationItem> result;

    for (const auto& s: std::get<std::vector<Student>>(students)) {
        result.push_back({
            s.id().toInt(),
            s.fullName()
        });
    }
    return result;
}

std::variant<std::vector<Program>, QString> ProgramStudentAssociationService::fetchPrograms(int studentId) const
{
    auto programs = repo_.programsForStudent(studentId);
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

std::optional<QString> ProgramStudentAssociationService::link(int programId, int studentId)
{
    return repo_.assignStudent(programId, studentId);
}

std::optional<QString> ProgramStudentAssociationService::unlink(int programId, int studentId)
{
    return repo_.removeStudent(programId, studentId);
}

#include "programstudentassociationservice.h"

ProgramStudentAssociationService::ProgramStudentAssociationService(ProgramStudentRepository& repo)
    : repo_(repo)
{}

std::vector<AssociationItem> ProgramStudentAssociationService::fetchAvailable(int programId) const
{
    auto students = repo_.studentsNotInProgram(programId);
    std::vector<AssociationItem> result;

    for (const auto& s: students) {
        result.push_back({
            s.id().toInt(),
            s.fullName()
        });
    }
    return result;
}

std::vector<AssociationItem> ProgramStudentAssociationService::fetchAssigned(int programId) const
{
    auto students = repo_.studentsForProgram(programId);
    std::vector<AssociationItem> result;

    for (const auto& s: students) {
        result.push_back({
            s.id().toInt(),
            s.fullName()
        });
    }
    return result;
}

std::vector<Program> ProgramStudentAssociationService::fetchPrograms(int studentId) const
{
    auto programs = repo_.programsForStudent(studentId);
    std::vector<Program> result;

    for (const auto& t: programs) {
        result.push_back({
            t.id(),
            t.name()
        });
    }
    return result;
}

void ProgramStudentAssociationService::link(int programId, int studentId)
{
    repo_.assignStudent(programId, studentId);
}

void ProgramStudentAssociationService::unlink(int programId, int studentId)
{
    repo_.removeStudent(programId, studentId);
}

#ifndef FAKEPROGRAMSTUDENTREPOSITORY_H
#define FAKEPROGRAMSTUDENTREPOSITORY_H
#include "../../src/infra/repositories/programstudentrepository.h"
#include "../../src/domain/program.h"

class FakeProgramStudentRepository : public ProgramStudentRepository
{
public:
    FakeProgramStudentRepository() : ProgramStudentRepository(QSqlDatabase()) {}

    bool assignCalled = false;
    bool deleteCalled = false;
    int assignedId = -1;
    int deletedId = -1;

    std::vector<Program> programs;
    std::vector<Student> students;

    std::variant<std::vector<Student>, QString> studentsForProgram(int programId) const override
    {
        return students;
    }

    std::variant<std::vector<Student>, QString> studentsNotInProgram(int programId) const override
    {
        return students;
    }

    std::variant<std::vector<Program>, QString> programsForStudent(int studentId) const override
    {
        return programs;
    }

    std::optional<QString> assignStudent(int programId, int studentId) override
    {
        assignCalled = true;
        assignedId = studentId;
        return std::nullopt;
    }

    std::optional<QString> removeStudent(int programId, int studentId) override
    {
        deleteCalled = true;
        deletedId = studentId;
        return std::nullopt;
    }
};
#endif // FAKEPROGRAMSTUDENTREPOSITORY_H

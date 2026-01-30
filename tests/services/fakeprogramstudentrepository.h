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

    std::vector<Student> studentsForProgram(int programId) const override
    {
        return students;
    }

    std::vector<Student> studentsNotInProgram(int programId) const override
    {
        return students;
    }

    std::vector<Program> programsForStudent(int studentId) const override
    {
        return programs;
    }

    void assignStudent(int programId, int studentId) override
    {
        assignCalled = true;
        assignedId = studentId;
        return;
    }

    void removeStudent(int programId, int studentId) override
    {
        deleteCalled = true;
        deletedId = studentId;
        return;
    }
};
#endif // FAKEPROGRAMSTUDENTREPOSITORY_H

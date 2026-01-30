#ifndef FAKEPROGRAMTEACHERREPOSITORY_H
#define FAKEPROGRAMTEACHERREPOSITORY_H
#include "../../src/infra/repositories/programteacherrepository.h"
#include "../../src/domain/program.h"

class FakeProgramTeacherRepository : public ProgramTeacherRepository
{
public:
    FakeProgramTeacherRepository() : ProgramTeacherRepository(QSqlDatabase()) {}

    bool assignCalled = false;
    bool deleteCalled = false;
    int assignedId = -1;
    int deletedId = -1;

    std::vector<Program> programs;
    std::vector<Teacher> teachers;

    std::vector<Teacher> teachersForProgram(int programId) const override
    {
        return teachers;
    }

    std::vector<Teacher> teachersNotInProgram(int programId) const override
    {
        return teachers;
    }

    std::vector<Program> programsForTeacher(int teacherId) const override
    {
        return programs;
    }

    void assignTeacher(int programId, int teacherId) override
    {
        assignCalled = true;
        assignedId = teacherId;
        return;
    }

    void removeTeacher(int programId, int teacherId) override
    {
        deleteCalled = true;
        deletedId = teacherId;
        return;
    }
};


#endif // FAKEPROGRAMTEACHERREPOSITORY_H

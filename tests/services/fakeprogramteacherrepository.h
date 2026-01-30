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

    std::variant<std::vector<Teacher>, QString> teachersForProgram(int programId) const override
    {
        return teachers;
    }

    std::variant<std::vector<Teacher>, QString> teachersNotInProgram(int programId) const override
    {
        return teachers;
    }

    std::variant<std::vector<Program>, QString> programsForTeacher(int teacherId) const override
    {
        return programs;
    }

    std::optional<QString> assignTeacher(int programId, int teacherId) override
    {
        assignCalled = true;
        assignedId = teacherId;
        return std::nullopt;
    }

    std::optional<QString> removeTeacher(int programId, int teacherId) override
    {
        deleteCalled = true;
        deletedId = teacherId;
        return std::nullopt;
    }
};


#endif // FAKEPROGRAMTEACHERREPOSITORY_H

#ifndef FAKEPROGRAMREPOSITORY_H
#define FAKEPROGRAMREPOSITORY_H
#include "../../src/infra/repositories/programrepository.h"
#include "../../src/domain/program.h"

class FakeProgramRepository : public ProgramRepository
{
public:
    FakeProgramRepository() : ProgramRepository(QSqlDatabase()) {}

    bool insertCalled = false;
    bool deleteCalled = false;
    int deletedId = -1;

    std::vector<Program> programs;

    bool insertProgram(int schoolId, const Program& program) override
    {
        insertCalled = true;
        programs.push_back(program);
        return true;
    }

    std::vector<Program> getPrograms() const override
    {
        return programs;
    }

    bool deleteProgram(int programId)  override
    {
        deleteCalled = true;
        deletedId = programId;
        return true;
    }
};

#endif // FAKEPROGRAMREPOSITORY_H

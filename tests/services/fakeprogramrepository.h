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

    std::optional<QString> insertProgram(int schoolId, const Program& program) override
    {
        insertCalled = true;
        programs.push_back(program);
        return std::nullopt;
    }

    std::variant<std::vector<Program>, QString> getPrograms() const override
    {
        return programs;
    }

    std::optional<QString> deleteProgram(int programId)  override
    {
        deleteCalled = true;
        deletedId = programId;
        return std::nullopt;
    }
};

#endif // FAKEPROGRAMREPOSITORY_H

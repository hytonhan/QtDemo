#include "programservice.h"

ProgramService::ProgramService(ProgramRepository& repo)
    : repo_(repo) {}


std::optional<QString> ProgramService::addProgram(int schoolId, const Program& program) const
{
    return repo_.insertProgram(schoolId, program);
}

std::optional<QString> ProgramService::removeProgram(int programId) const
{
    return repo_.deleteProgram(programId);
}

std::variant<std::vector<Program>, QString> ProgramService::fetchPrograms() const
{
    return repo_.getPrograms();
}

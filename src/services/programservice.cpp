#include "programservice.h"

ProgramService::ProgramService(ProgramRepository& repo)
    : repo_(repo) {}


void ProgramService::addProgram(int schoolId, const Program& program) const
{
    repo_.insertProgram(schoolId, program);
}

void ProgramService::removeProgram(int programId) const
{
    repo_.deleteProgram(programId);
}

std::vector<Program> ProgramService::fetchPrograms() const
{
    return repo_.getPrograms();
}

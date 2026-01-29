#include "programservice.h"

ProgramService::ProgramService(ProgramRepository& repo)
    : repo_(repo) {}


void ProgramService::addProgram(int schoolId, const Program& program)
{
    repo_.insertProgram(schoolId, program);
}

void ProgramService::removeProgram(int programId)
{
    repo_.deleteProgram(programId);
}

std::vector<Program> ProgramService::fetchPrograms()
{
    return repo_.getPrograms();
}

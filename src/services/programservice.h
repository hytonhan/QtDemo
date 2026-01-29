#ifndef PROGRAMSERVICE_H
#define PROGRAMSERVICE_H

#pragma once

#include "../domain/program.h"
#include "../infra/repositories/programrepository.h"

class ProgramService
{
public:
    explicit ProgramService(ProgramRepository& repo);

    void addProgram(int schoolId, const Program& program);
    void removeProgram(int programId);
    std::vector<Program> fetchPrograms();

private:
    ProgramRepository& repo_;
};

#endif // PROGRAMSERVICE_H

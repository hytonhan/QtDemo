#ifndef PROGRAMSERVICE_H
#define PROGRAMSERVICE_H

#pragma once

#include "../domain/program.h"
#include "../infra/repositories/programrepository.h"

class ProgramService
{
public:
    explicit ProgramService(ProgramRepository& repo);

    void addProgram(int schoolId, const Program& program) const;
    void removeProgram(int programId) const;
    std::vector<Program> fetchPrograms() const;

private:
    ProgramRepository& repo_;
};

#endif // PROGRAMSERVICE_H

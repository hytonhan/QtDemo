#ifndef PROGRAMSERVICE_H
#define PROGRAMSERVICE_H

#pragma once

#include "../domain/program.h"
#include "../infra/repositories/programrepository.h"

class ProgramService
{
public:
    explicit ProgramService(ProgramRepository& repo);

    std::optional<QString> addProgram(int schoolId, const Program& program) const;
    std::optional<QString> removeProgram(int programId) const;
    std::variant<std::vector<Program>, QString> fetchPrograms() const;

private:
    ProgramRepository& repo_;
};

#endif // PROGRAMSERVICE_H

#ifndef PROGRAMREPOSITORY_H
#define PROGRAMREPOSITORY_H

#pragma once

#include <QString>
#include <vector>
#include <QSqlDatabase>
#include "../../domain/program.h"

class ProgramRepository
{
public:
    explicit ProgramRepository(const QSqlDatabase& db);
    virtual ~ProgramRepository() = default;

    virtual bool insertProgram(int schoolId, const Program& program);
    virtual std::vector<Program> getPrograms() const;
    virtual bool deleteProgram(int programId);

private:
    QSqlDatabase db_;
};

#endif // KOULUTUSOHJELMAREPOSITORY_H

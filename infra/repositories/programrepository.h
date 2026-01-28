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
    explicit ProgramRepository(QSqlDatabase db);

    bool insertProgram(int schoolId, const Program& program);
    std::vector<Program> getPrograms() const;
    bool deleteProgram(int programId);

private:
    QSqlDatabase db_;
};

#endif // KOULUTUSOHJELMAREPOSITORY_H

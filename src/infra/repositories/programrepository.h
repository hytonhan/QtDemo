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

    virtual std::optional<QString> insertProgram(int schoolId, const Program& program);
    virtual std::variant<std::vector<Program>, QString> getPrograms() const;
    virtual std::optional<QString> deleteProgram(int programId);

private:
    QSqlDatabase db_;
};

#endif // KOULUTUSOHJELMAREPOSITORY_H

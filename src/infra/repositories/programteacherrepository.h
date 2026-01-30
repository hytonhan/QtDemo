#ifndef PROGRAMTEACHERREPOSITORY_H
#define PROGRAMTEACHERREPOSITORY_H

#pragma once

#include <QSqlDatabase>
#include <vector>
#include "../../domain/teacher.h"
#include "../../domain/program.h"

class ProgramTeacherRepository
{
public:
    explicit ProgramTeacherRepository(const QSqlDatabase& db);
    virtual ~ProgramTeacherRepository() = default;

    virtual std::variant<std::vector<Teacher>, QString> teachersForProgram(int programId) const;
    virtual std::variant<std::vector<Teacher>, QString> teachersNotInProgram(int programId) const;
    virtual std::variant<std::vector<Program>, QString> programsForTeacher(int teacherId) const;

    virtual std::optional<QString> assignTeacher(int programId, int teacherId);
    virtual std::optional<QString> removeTeacher(int programId, int teacherId);
private:
    QSqlDatabase db_;
};

#endif // KOULUTUSOHJELMAOPETTAJAREPOSITORY_H

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
    explicit ProgramTeacherRepository(QSqlDatabase db);
    virtual ~ProgramTeacherRepository() = default;
    virtual std::vector<Teacher> teachersForProgram(int programId);
    virtual std::vector<Teacher> teachersNotInProgram(int programId);
    virtual std::vector<Program> programsForTeacher(int teacherId);

    virtual void assignTeacher(int programId, int teacherId);
    virtual void removeTeacher(int programId, int teacherId);
private:
    QSqlDatabase db_;
};

#endif // KOULUTUSOHJELMAOPETTAJAREPOSITORY_H

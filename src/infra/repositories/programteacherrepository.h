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

    std::vector<Teacher> teachersForProgram(int programId);
    std::vector<Teacher> teachersNotInProgram(int programId);
    std::vector<Program> programsForTeacher(int teacherId);

    void assignTeacher(int programId, int teacherId);
    void removeTeacher(int programId, int teacherId);
private:
    QSqlDatabase db_;
};

#endif // KOULUTUSOHJELMAOPETTAJAREPOSITORY_H

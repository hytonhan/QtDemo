#ifndef PROGRAMSTUDENTREPOSITORY_H
#define PROGRAMSTUDENTREPOSITORY_H

#pragma once

#include <QSqlDatabase>
#include <vector>
#include "../../domain/student.h"
#include "../../domain/program.h"

class ProgramStudentRepository
{
public:
    explicit ProgramStudentRepository(QSqlDatabase db);

    std::vector<Student> studentsForProgram(int programId);
    std::vector<Student> studentsNotInProgram(int programId);
    std::vector<Program> programsForStudent(int studentId);

    void assignStudent(int programId, int studentId);
    void removeStudent(int programId, int studentId);
private:
    QSqlDatabase db_;
};

#endif // PROGRAMSTUDENTREPOSITORY_H

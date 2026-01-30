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
    explicit ProgramStudentRepository(const QSqlDatabase& db);
    virtual ~ProgramStudentRepository() = default;

    virtual std::vector<Student> studentsForProgram(int programId)  const;
    virtual std::vector<Student> studentsNotInProgram(int programId)  const;
    virtual std::vector<Program> programsForStudent(int studentId) const;

    virtual void assignStudent(int programId, int studentId);
    virtual void removeStudent(int programId, int studentId);
private:
    QSqlDatabase db_;
};

#endif // PROGRAMSTUDENTREPOSITORY_H

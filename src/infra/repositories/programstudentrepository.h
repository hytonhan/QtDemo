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

    virtual std::variant<std::vector<Student>, QString> studentsForProgram(int programId)  const;
    virtual std::variant<std::vector<Student>, QString> studentsNotInProgram(int programId)  const;
    virtual std::variant<std::vector<Program>, QString> programsForStudent(int studentId) const;

    virtual std::optional<QString> assignStudent(int programId, int studentId);
    virtual std::optional<QString> removeStudent(int programId, int studentId);
private:
    QSqlDatabase db_;
};

#endif // PROGRAMSTUDENTREPOSITORY_H

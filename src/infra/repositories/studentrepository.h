#ifndef STUDENTREPOSITORY_H
#define STUDENTREPOSITORY_H

#pragma once

#include <QString>
#include <vector>
#include <QSqlDatabase>
#include "../../domain/student.h"

class StudentRepository
{
public:
    explicit StudentRepository(const QSqlDatabase& db);

    std::optional<QString> insertStudent(const Student& student);
    std::variant<std::vector<Student>, QString> getStudents() const;
    std::optional<QString> deleteStudent(const Student& student);

private:
    QSqlDatabase db_;
};

#endif // STUDENTREPOSITORY_H

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

    bool insertStudent(const Student& student);
    std::vector<Student> getStudents() const;
    bool deleteStudent(const Student& student);

private:
    QSqlDatabase db_;
};

#endif // STUDENTREPOSITORY_H

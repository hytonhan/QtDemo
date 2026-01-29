#ifndef TEACHERREPOSITORY_H
#define TEACHERREPOSITORY_H

#pragma once

#include <QString>
#include <vector>
#include <QSqlDatabase>
#include "../../domain/teacher.h"

class TeacherRepository
{
public:
    explicit TeacherRepository(QSqlDatabase db);

    bool insertTeacher(const Teacher& teacher);
    std::vector<Teacher> getTeachers() const;
    bool deleteTeacher(int teacherId);

private:
    QSqlDatabase db_;
};

#endif // TEACHERREPOSITORY_H

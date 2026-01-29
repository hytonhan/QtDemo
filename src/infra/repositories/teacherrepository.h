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
    virtual ~TeacherRepository() = default;

    virtual bool insertTeacher(const Teacher& teacher);
    virtual std::vector<Teacher> getTeachers() const;
    virtual bool deleteTeacher(int teacherId);

private:
    QSqlDatabase db_;
};

#endif // TEACHERREPOSITORY_H

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
    explicit TeacherRepository(const QSqlDatabase& db);
    virtual ~TeacherRepository() = default;

    virtual std::optional<QString> insertTeacher(const Teacher& teacher);
    virtual std::variant<std::vector<Teacher>, QString> getTeachers() const;
    virtual std::optional<QString> deleteTeacher(int teacherId);

private:
    QSqlDatabase db_;
};

#endif // TEACHERREPOSITORY_H

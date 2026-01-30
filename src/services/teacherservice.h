#ifndef TEACHERSERVICE_H
#define TEACHERSERVICE_H

#pragma once

#include "../domain/teacher.h"
#include "../infra/repositories/teacherrepository.h"

class TeacherService
{
public:
    explicit TeacherService(TeacherRepository& repo);

    std::optional<QString> addTeacher(const Teacher& teacher) const;
    std::optional<QString> removeTeacher(int teacherId) const;
    std::variant<std::vector<Teacher>, QString> fetchTeachers() const;
private:
    TeacherRepository& repo_;
};

#endif // TEACHERSERVICE_H

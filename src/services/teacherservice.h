#ifndef TEACHERSERVICE_H
#define TEACHERSERVICE_H

#pragma once

#include "../domain/teacher.h"
#include "../infra/repositories/teacherrepository.h"

class TeacherService
{
public:
    explicit TeacherService(TeacherRepository& repo);

    void addTeacher(const Teacher& teacher);
    void removeTeacher(int teacherId);
    std::vector<Teacher> fetchTeacher();
private:
    TeacherRepository& repo_;
};

#endif // TEACHERSERVICE_H

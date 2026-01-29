#include "teacherservice.h"

TeacherService::TeacherService(TeacherRepository& repo)
    : repo_(repo)
{}

void TeacherService::addTeacher(const Teacher& teacher)
{
    repo_.insertTeacher(teacher);
}

void TeacherService::removeTeacher(int teacherId)
{
    repo_.deleteTeacher(teacherId);
}

std::vector<Teacher> TeacherService::fetchTeachers()
{
    return repo_.getTeachers();
}

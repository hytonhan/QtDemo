#include "teacherservice.h"

TeacherService::TeacherService(TeacherRepository& repo)
    : repo_(repo)
{}

void TeacherService::addTeacher(const Teacher& teacher) const
{
    repo_.insertTeacher(teacher);
}

void TeacherService::removeTeacher(int teacherId) const
{
    repo_.deleteTeacher(teacherId);
}

std::vector<Teacher> TeacherService::fetchTeachers() const
{
    return repo_.getTeachers();
}

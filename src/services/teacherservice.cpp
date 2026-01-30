#include "teacherservice.h"

TeacherService::TeacherService(TeacherRepository& repo)
    : repo_(repo)
{}

std::optional<QString> TeacherService::addTeacher(const Teacher& teacher) const
{
    return repo_.insertTeacher(teacher);
}

std::optional<QString> TeacherService::removeTeacher(int teacherId) const
{
    return repo_.deleteTeacher(teacherId);
}

std::variant<std::vector<Teacher>, QString> TeacherService::fetchTeachers() const
{
    return repo_.getTeachers();
}

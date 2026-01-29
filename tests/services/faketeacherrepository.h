#include "../../src/infra/repositories/teacherrepository.h"
#include "../../src/domain/teacher.h"

class FakeTeacherRepository : public TeacherRepository
{
public:
    FakeTeacherRepository() : TeacherRepository(QSqlDatabase()) {}

    bool insertCalled = false;
    bool deleteCalled = false;
    int deletedId = -1;

    std::vector<Teacher> teachers;

    bool insertTeacher(const Teacher& teacher) override
    {
        insertCalled = true;
        teachers.push_back(teacher);
        return true;
    }

    std::vector<Teacher> getTeachers() const override
    {
        return teachers;
    }

    bool deleteTeacher(int teacherId)  override
    {
        deleteCalled = true;
        deletedId = teacherId;
        return true;
    }
};

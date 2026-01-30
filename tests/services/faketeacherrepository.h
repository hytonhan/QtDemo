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

    std::optional<QString> insertTeacher(const Teacher& teacher) override
    {
        insertCalled = true;
        teachers.push_back(teacher);
        return std::nullopt;
    }

    std::variant<std::vector<Teacher>, QString> getTeachers() const override
    {
        return teachers;
    }

    std::optional<QString> deleteTeacher(int teacherId)  override
    {
        deleteCalled = true;
        deletedId = teacherId;
        return std::nullopt;
    }
};

#include <QtTest>
#include "../../src/services/teacherservice.h"
#include "faketeacherrepository.h"

class TestTeacherService : public QObject
{
    Q_OBJECT

private slots:
    void newTeacherIsAdded();
    void teacherIsRemoved();
    void teachersAreReturned();
};

void TestTeacherService::newTeacherIsAdded()
{
    FakeTeacherRepository fakeRepo;
    TeacherService service(fakeRepo);

    Teacher t("First", "Last", "address", "phone", "1", 123.0, "field");
    service.addTeacher(t);

    QVERIFY(fakeRepo.insertCalled);
}

void TestTeacherService::teacherIsRemoved()
{
    FakeTeacherRepository repo;
    TeacherService service(repo);

    service.removeTeacher(42);

    QVERIFY(repo.deleteCalled);
    QCOMPARE(repo.deletedId, 42);
}

void TestTeacherService::teachersAreReturned()
{
    FakeTeacherRepository repo;
    repo.teachers.push_back(
        Teacher("first", "last", "", "", "2", 4200, "CS")
        );

    TeacherService service(repo);
    auto result = std::get<std::vector<Teacher>>(service.fetchTeachers());

    QCOMPARE(result.size(), 1);
    QCOMPARE(result[0].firstName(), QString("first"));
}

QTEST_MAIN(TestTeacherService)
#include "test_teacherservice.moc"

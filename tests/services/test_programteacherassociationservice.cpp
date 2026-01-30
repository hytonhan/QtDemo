#include <QtTest>
#include "../../src/services/programteacherassociationservice.h"
#include "fakeprogramteacherrepository.h"

class TestProgramTeacherAssociationService : public QObject
{
    Q_OBJECT

private slots:
    void teacherIsAssignedWithProgram();
    void teacherIsUnAssignedWithProgram();
    void programsAreReturned();
    void teachersInProgramAreReturned();
    void teachersNotInProgramsAreReturned();
};

void TestProgramTeacherAssociationService::teacherIsAssignedWithProgram()
{
    FakeProgramTeacherRepository fakeRepo;
    ProgramTeacherAssociationService service(fakeRepo);

    Teacher t("first", "last", "address", "phone", "id", 1234.0, "field");
    service.link(1, t.id().toInt());

    QVERIFY(fakeRepo.assignCalled);
}

void TestProgramTeacherAssociationService::teacherIsUnAssignedWithProgram()
{
    FakeProgramTeacherRepository repo;
    ProgramTeacherAssociationService service(repo);

    service.unlink(1, 1);

    QVERIFY(repo.deleteCalled);
    QCOMPARE(repo.deletedId, 1);
}

void TestProgramTeacherAssociationService::programsAreReturned()
{
    FakeProgramTeacherRepository repo;
    repo.programs.push_back(
        Program("id", "name")
        );

    ProgramTeacherAssociationService service(repo);
    auto result = std::get<std::vector<Program>>(service.fetchPrograms(1));

    QCOMPARE(result.size(), 1);
    QCOMPARE(result[0].name(), QString("name"));
}

void TestProgramTeacherAssociationService::teachersInProgramAreReturned()
{
    FakeProgramTeacherRepository repo;
    repo.teachers.push_back(
        Teacher("first", "last", "address", "phone", "id", 1234.0, "field")
        );

    ProgramTeacherAssociationService service(repo);
    auto result = std::get<std::vector<AssociationItem>>(service.fetchAssigned(1));

    QCOMPARE(result.size(), 1);
    QCOMPARE(result[0].displayName, QString("first last"));
}

void TestProgramTeacherAssociationService::teachersNotInProgramsAreReturned()
{
    FakeProgramTeacherRepository repo;
    repo.teachers.push_back(
        Teacher("first", "last", "address", "phone", "id", 1234.0, "field")
        );

    ProgramTeacherAssociationService service(repo);
    auto result = std::get<std::vector<AssociationItem>>(service.fetchAvailable(1));

    QCOMPARE(result.size(), 1);
    QCOMPARE(result[0].displayName, QString("first last"));
}

QTEST_MAIN(TestProgramTeacherAssociationService)
#include "test_programteacherassociationservice.moc"

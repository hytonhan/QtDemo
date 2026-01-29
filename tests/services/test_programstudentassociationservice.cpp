#include <QtTest>
#include "../../src/services/programstudentassociationservice.h"
#include "fakeprogramstudentrepository.h"

class TestProgramStudentAssociationService : public QObject
{
    Q_OBJECT

private slots:
    void studentIsAssignedWithProgram();
    void studentIsUnAssignedWithProgram();
    void programsAreReturned();
    void studentsInProgramAreReturned();
    void studentsNotInProgramsAreReturned();
};

void TestProgramStudentAssociationService::studentIsAssignedWithProgram()
{
    FakeProgramStudentRepository fakeRepo;
    ProgramStudentAssociationService service(fakeRepo);

    Student t("first", "last", "address", "phone", "id");
    service.link(1, t.id().toInt());

    QVERIFY(fakeRepo.assignCalled);
}

void TestProgramStudentAssociationService::studentIsUnAssignedWithProgram()
{
    FakeProgramStudentRepository repo;
    ProgramStudentAssociationService service(repo);

    service.unlink(1, 1);

    QVERIFY(repo.deleteCalled);
    QCOMPARE(repo.deletedId, 1);
}

void TestProgramStudentAssociationService::programsAreReturned()
{
    FakeProgramStudentRepository repo;
    repo.programs.push_back(
        Program("id", "name")
        );

    ProgramStudentAssociationService service(repo);
    auto result = service.fetchPrograms(1);

    QCOMPARE(result.size(), 1);
    QCOMPARE(result[0].name(), QString("name"));
}

void TestProgramStudentAssociationService::studentsInProgramAreReturned()
{
    FakeProgramStudentRepository repo;
    repo.students.push_back(
        Student("first", "last", "address", "phone", "id")
        );

    ProgramStudentAssociationService service(repo);
    auto result = service.fetchAssigned(1);

    QCOMPARE(result.size(), 1);
    QCOMPARE(result[0].displayName, QString("first last"));
}

void TestProgramStudentAssociationService::studentsNotInProgramsAreReturned()
{
    FakeProgramStudentRepository repo;
    repo.students.push_back(
        Student("first", "last", "address", "phone", "id")
        );

    ProgramStudentAssociationService service(repo);
    auto result = service.fetchAvailable(1);

    QCOMPARE(result.size(), 1);
    QCOMPARE(result[0].displayName, QString("first last"));
}

QTEST_MAIN(TestProgramStudentAssociationService)
#include "test_programstudentassociationservice.moc"

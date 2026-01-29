#include <QtTest>
#include "../../src/services/programservice.h"
#include "fakeprogramrepository.h"

class TestProgramService : public QObject
{
    Q_OBJECT

private slots:
    void newProgramIsAdded();
    void programIsRemoved();
    void programsAreReturned();
};

void TestProgramService::newProgramIsAdded()
{
    FakeProgramRepository fakeRepo;
    ProgramService service(fakeRepo);

    Program p("id", "name");
    service.addProgram(1, p);

    QVERIFY(fakeRepo.insertCalled);
}

void TestProgramService::programIsRemoved()
{
    FakeProgramRepository repo;
    ProgramService service(repo);

    service.removeProgram(1);

    QVERIFY(repo.deleteCalled);
    QCOMPARE(repo.deletedId, 1);
}

void TestProgramService::programsAreReturned()
{
    FakeProgramRepository repo;
    repo.programs.push_back(
        Program("id", "name")
        );

    ProgramService service(repo);
    auto result = service.fetchPrograms();

    QCOMPARE(result.size(), 1);
    QCOMPARE(result[0].name(), QString("name"));
}

QTEST_MAIN(TestProgramService)
#include "test_programservice.moc"

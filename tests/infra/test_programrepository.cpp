#include <QtTest>
#include "../../src/infra/repositories/programrepository.h"
#include "../../src/infra/databaseservice.h"
#include <QSqlQuery>


class TestProgramRepository : public QObject
{
    Q_OBJECT

private:
    QSqlDatabase db;

private slots:
    void init();
    void initTestCase();
    void insertAndFetchProgram();
    void insertAndDeleteProgram();
};

void TestProgramRepository::initTestCase()
{
    Q_INIT_RESOURCE(resources);
}

void TestProgramRepository::init()
{
    db = QSqlDatabase();
    DatabaseService::instance().resetConnection();
    DatabaseService& dbService = DatabaseService::instance();
    dbService.openDatabase(":memory:");
    dbService.initializeSchema();
    db = dbService.database();
    QSqlQuery query(db);
    query.exec("INSERT INTO school (id, name) VALUES (1, 'TAMK')");
}

void TestProgramRepository::insertAndFetchProgram()
{
    ProgramRepository repo(db);

    Program p("1", "name");
    QVERIFY(repo.insertProgram(1 ,p));

    auto programs = repo.getPrograms();
    QCOMPARE(programs.size(), 1);
    QCOMPARE(programs[0].name(), QString("name"));
}

void TestProgramRepository::insertAndDeleteProgram()
{
    ProgramRepository repo(db);

    Program p("1", "name");
    QVERIFY(repo.insertProgram(1, p));

    QVERIFY(repo.deleteProgram(p.id().toInt()));

    auto programs = repo.getPrograms();
    QCOMPARE(programs.size(), 0);
}


QTEST_MAIN(TestProgramRepository)
#include "test_programrepository.moc"

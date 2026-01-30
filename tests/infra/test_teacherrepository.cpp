#include <QtTest>
#include "../../src/infra/repositories/teacherrepository.h"
#include "../../src/infra/databaseservice.h"
#include <QSqlQuery>

class TestTeacherRepository : public QObject
{
    Q_OBJECT

private:
    QSqlDatabase db;

private slots:
    void init();
    void initTestCase();
    void insertAndFetchTeacher();
    void insertAndDeleteTeacher();
};

void TestTeacherRepository::initTestCase()
{
    Q_INIT_RESOURCE(resources);
}

void TestTeacherRepository::init()
{
    db = QSqlDatabase();
    DatabaseService::instance().resetConnection();
    DatabaseService& dbService = DatabaseService::instance();
    dbService.openDatabase(":memory:");
    dbService.initializeSchema();
    db = dbService.database();
}

void TestTeacherRepository::insertAndFetchTeacher()
{
    TeacherRepository repo(db);

    Teacher t("first", "last", "address", "phone", "1", 4500, "field");
    QVERIFY(!repo.insertTeacher(t));

    auto teachers = std::get<std::vector<Teacher>>(repo.getTeachers());
    QCOMPARE(teachers.size(), 1);
    QCOMPARE(teachers[0].field(), QString("field"));
}

void TestTeacherRepository::insertAndDeleteTeacher()
{
    TeacherRepository repo(db);

    Teacher t("first", "last", "address", "phone", "1", 4500, "field");
    QVERIFY(!repo.insertTeacher(t));

    QVERIFY(!repo.deleteTeacher(t.id().toInt()));

    auto teachers = std::get<std::vector<Teacher>>(repo.getTeachers());
    QCOMPARE(teachers.size(), 0);
}


QTEST_MAIN(TestTeacherRepository)
#include "test_teacherrepository.moc"

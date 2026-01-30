#include <QtTest>
#include "../../src/infra/repositories/studentrepository.h"
#include "../../src/infra/databaseservice.h"
#include <QSqlQuery>

class TestStudentRepository : public QObject
{
    Q_OBJECT

private:
    QSqlDatabase db;

private slots:
    void init();
    void initTestCase();
    void insertAndFetchStudent();
    void insertAndDeleteStudent();
};

void TestStudentRepository::initTestCase()
{
    Q_INIT_RESOURCE(resources);
}

void TestStudentRepository::init()
{
    db = QSqlDatabase();
    DatabaseService::instance().resetConnection();
    DatabaseService& dbService = DatabaseService::instance();
    dbService.openDatabase(":memory:");
    dbService.initializeSchema();
    db = dbService.database();
}

void TestStudentRepository::insertAndFetchStudent()
{
    StudentRepository repo(db);

    Student s("first", "last", "address", "phone", "1");
    QVERIFY(!repo.insertStudent(s));

    auto students = std::get<std::vector<Student>>(repo.getStudents());
    QCOMPARE(students.size(), 1);
    QCOMPARE(students[0].firstName(), QString("first"));
}

void TestStudentRepository::insertAndDeleteStudent()
{
    StudentRepository repo(db);

    Student s("first", "last", "address", "phone", "1");
    QVERIFY(!repo.insertStudent(s));

    QVERIFY(!repo.deleteStudent(s));

    auto students = std::get<std::vector<Student>>(repo.getStudents());
    QCOMPARE(students.size(), 0);
}


QTEST_MAIN(TestStudentRepository)
#include "test_studentrepository.moc"

#include <QtTest>
#include <QSqlQuery>
#include "../../src/infra/repositories/programstudentrepository.h"
#include "../../src/infra/repositories/studentrepository.h"
#include "../../src/infra/repositories/programrepository.h"
#include "../../src/infra/databaseservice.h"

class TestProgramStudentRepository : public QObject
{
    Q_OBJECT

private:
    QSqlDatabase db;

private slots:
    void init();
    void initTestCase();
    void assignAndFetchStudents();
    void removeStudentFromProgram();
    void fetchStudentsNotInProgram();
    void fetchProgramsForStudent();
};

void TestProgramStudentRepository::initTestCase()
{
    Q_INIT_RESOURCE(resources);
}

void TestProgramStudentRepository::init()
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

void TestProgramStudentRepository::assignAndFetchStudents()
{
    StudentRepository studentRepo(db);
    ProgramRepository programRepo(db);
    ProgramStudentRepository repo(db);

    studentRepo.insertStudent(
        Student("first", "last", "address", "phone", "1")
        );
    programRepo.insertProgram(1, Program("1", "name"));

    repo.assignStudent(1, 1);

    auto students = repo.studentsForProgram(1);
    QCOMPARE(students.size(), 1);
    QCOMPARE(students[0].firstName(), QString("first"));
}

void TestProgramStudentRepository::removeStudentFromProgram()
{
    StudentRepository studentRepo(db);
    ProgramRepository programRepo(db);
    ProgramStudentRepository repo(db);

    studentRepo.insertStudent(
        Student("first", "last", "address", "phone", "1")
        );
    programRepo.insertProgram(1, Program("1", "name"));

    repo.assignStudent(1, 1);

    auto students = repo.studentsForProgram(1);
    QCOMPARE(students.size(), 1);
    QCOMPARE(students[0].lastName(), QString("last"));

    repo.removeStudent(1, 1);
    students = repo.studentsForProgram(1);
    QCOMPARE(students.size(), 0);
}

void TestProgramStudentRepository::fetchStudentsNotInProgram()
{
    StudentRepository studentRepo(db);
    ProgramRepository programRepo(db);
    ProgramStudentRepository repo(db);

    studentRepo.insertStudent(
        Student("first", "last", "address", "phone", "1")
        );
    studentRepo.insertStudent(
        Student("second", "secondlast", "address", "phone", "2")
        );
    programRepo.insertProgram(1, Program("1", "name"));
    repo.assignStudent(1, 1);

    auto students = repo.studentsNotInProgram(1);
    QCOMPARE(students.size(), 1);
    QCOMPARE(students[0].firstName(), QString("second"));
}

void TestProgramStudentRepository::fetchProgramsForStudent()
{
    StudentRepository studentRepo(db);
    ProgramRepository programRepo(db);
    ProgramStudentRepository repo(db);

    studentRepo.insertStudent(
        Student("first", "last", "address", "phone", "1")
        );
    programRepo.insertProgram(1, Program("1", "name"));
    programRepo.insertProgram(1, Program("2", "name2"));

    repo.assignStudent(1, 1);

    auto programs = repo.programsForStudent(1);
    QCOMPARE(programs.size(), 1);
    QCOMPARE(programs[0].name(), QString("name"));
}

QTEST_MAIN(TestProgramStudentRepository)
#include "test_programstudentrepository.moc"

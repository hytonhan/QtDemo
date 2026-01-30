#include <QtTest>
#include <QSqlQuery>
#include "../../src/infra/repositories/programteacherrepository.h"
#include "../../src/infra/repositories/teacherrepository.h"
#include "../../src/infra/repositories/programrepository.h"
#include "../../src/infra/databaseservice.h"

class TestProgramTeacherRepository : public QObject
{
    Q_OBJECT

private:
    QSqlDatabase db;

private slots:
    void init();
    void initTestCase();
    void assignAndFetchTeachers();
    void removeTeacherFromProgram();
    void fetchTeachersNotInProgram();
    void fetchProgramsForTeacher();
};

void TestProgramTeacherRepository::initTestCase()
{
    Q_INIT_RESOURCE(resources);
}

void TestProgramTeacherRepository::init()
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

void TestProgramTeacherRepository::assignAndFetchTeachers()
{
    TeacherRepository teacherRepo(db);
    ProgramRepository programRepo(db);
    ProgramTeacherRepository repo(db);

    teacherRepo.insertTeacher(
        Teacher("first", "last", "address", "phone", "1", 5000, "field")
        );
    programRepo.insertProgram(1, Program("1", "name"));

    repo.assignTeacher(1, 1);

    auto teachers = std::get<std::vector<Teacher>>(repo.teachersForProgram(1));
    QCOMPARE(teachers.size(), 1);
    QCOMPARE(teachers[0].field(), QString("field"));
}

void TestProgramTeacherRepository::removeTeacherFromProgram()
{
    TeacherRepository teacherRepo(db);
    ProgramRepository programRepo(db);
    ProgramTeacherRepository repo(db);

    teacherRepo.insertTeacher(
        Teacher("first", "last", "address", "phone", "1", 5000, "field")
        );
    programRepo.insertProgram(1, Program("1", "name"));

    repo.assignTeacher(1, 1);

    auto teachers = std::get<std::vector<Teacher>>(repo.teachersForProgram(1));
    QCOMPARE(teachers.size(), 1);
    QCOMPARE(teachers[0].field(), QString("field"));

    repo.removeTeacher(1, 1);
    teachers = std::get<std::vector<Teacher>>(repo.teachersForProgram(1));
    QCOMPARE(teachers.size(), 0);
}

void TestProgramTeacherRepository::fetchTeachersNotInProgram()
{
    TeacherRepository teacherRepo(db);
    ProgramRepository programRepo(db);
    ProgramTeacherRepository repo(db);

    teacherRepo.insertTeacher(
        Teacher("first", "last", "address", "phone", "1", 5000, "field")
        );
    teacherRepo.insertTeacher(
        Teacher("second", "secondlast", "address", "phone", "2", 5000, "field")
        );
    programRepo.insertProgram(1, Program("1", "name"));
    repo.assignTeacher(1, 1);

    auto teachers = std::get<std::vector<Teacher>>(repo.teachersNotInProgram(1));
    QCOMPARE(teachers.size(), 1);
    QCOMPARE(teachers[0].firstName(), QString("second"));
}

void TestProgramTeacherRepository::fetchProgramsForTeacher()
{
    TeacherRepository teacherRepo(db);
    ProgramRepository programRepo(db);
    ProgramTeacherRepository repo(db);

    teacherRepo.insertTeacher(
        Teacher("first", "last", "address", "phone", "1", 5000, "field")
        );
    programRepo.insertProgram(1, Program("1", "name"));
    programRepo.insertProgram(1, Program("2", "name2"));

    repo.assignTeacher(1, 1);

    auto programs = std::get<std::vector<Program>>(repo.programsForTeacher(1));
    QCOMPARE(programs.size(), 1);
    QCOMPARE(programs[0].name(), QString("name"));
}

QTEST_MAIN(TestProgramTeacherRepository)
#include "test_programteacherrepository.moc"

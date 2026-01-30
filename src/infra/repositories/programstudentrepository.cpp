#include "programstudentrepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include "../../infra/databaseservice.h"

ProgramStudentRepository::ProgramStudentRepository(const QSqlDatabase& db) {}

std::vector<Student> ProgramStudentRepository::studentsForProgram(int programId) const
{
    QSqlQuery query(db_);
    const QString queryString = DatabaseService::loadSql(":/sql/sql/fetch_programstudents.sql");
    if (queryString.isEmpty()) {
        qCritical() << "Couldn't sql command file or it was empty.";
        return std::vector<Student>();
    }
    query.prepare(queryString);
    query.bindValue(":program_id", programId);

    if (!query.exec()) {
        auto foo = query.lastError().text();
        qCritical() << "Failed to fetch students of program" << query.lastError().text();
        return std::vector<Student>();
    }

    std::vector<Student> students;
    while(query.next()) {
        students.emplace_back(query.value("firstName").toString(),
                              query.value("lastName").toString(),
                              query.value("address").toString(),
                              query.value("phoneNumber").toString(),
                              query.value("id").toString());
    }
    return students;
}

std::vector<Student> ProgramStudentRepository::studentsNotInProgram(int programId) const
{
    QSqlQuery query(db_);
    const QString queryString = DatabaseService::loadSql(":/sql/sql/fetch_studentsnotinprogram.sql");
    if (queryString.isEmpty()) {
        qCritical() << "Couldn't sql command file or it was empty.";
        return std::vector<Student>();
    }
    query.prepare(queryString);

    query.bindValue(":program_id", programId);

    if (!query.exec()) {
        auto lastError = query.lastError().text();
        qCritical() << "Failed to fetch students not in program:" << query.lastError().text();
        return std::vector<Student>();
    }

    std::vector<Student> students;
    while(query.next()) {
        students.emplace_back(query.value("firstName").toString(),
                              query.value("lastName").toString(),
                              query.value("address").toString(),
                              query.value("phoneNumber").toString(),
                              query.value("id").toString());
    }
    return students;
}

std::vector<Program> ProgramStudentRepository::programsForStudent(int studentId) const
{
    QSqlQuery query(db_);
    const QString queryString = DatabaseService::loadSql(":/sql/sql/fetch_studentprograms.sql");
    if (queryString.isEmpty()) {
        qCritical() << "Couldn't sql command file or it was empty.";
        return std::vector<Program>();
    }
    query.prepare(queryString);
    query.bindValue(":student_id", studentId);
    if (!query.exec()) {
        auto lastError = query.lastError().text();
        qCritical() << "Failed to fetch programs of student" << query.lastError().text();
        return std::vector<Program>();
    }

    std::vector<Program> programs;
    while(query.next()) {
        programs.emplace_back(query.value("id").toString(),
                              query.value("name").toString());
    }
    return programs;
}

void ProgramStudentRepository::assignStudent(int programId, int studentId)
{
    QSqlQuery query(db_);
    const QString queryString = DatabaseService::loadSql(":/sql/sql/link_programstudent.sql");
    if (queryString.isEmpty()) {
        qCritical() << "Couldn't sql command file or it was empty.";
        return;
    }
    query.prepare(queryString);
    query.bindValue(":program_id", programId);
    query.bindValue(":student_id", studentId);

    if (!query.exec()) {
        qCritical() << "Failed to link student to program:"
                    << query.lastError().text();
        return;
    }
    return;
}

void ProgramStudentRepository::removeStudent(int programId, int studentId)
{
    QSqlQuery query(db_);
    const QString queryString = DatabaseService::loadSql(":/sql/sql/unlink_programstudent.sql");
    if (queryString.isEmpty()) {
        qCritical() << "Couldn't sql command file or it was empty.";
        return;
    }
    query.prepare(queryString);

    query.bindValue(":student_id", studentId);
    query.bindValue(":program_id", programId);

    if (!query.exec()) {
        qCritical() << "Failed to unlink student into program" << query.lastError().text();
        return;
    }
    return;
}

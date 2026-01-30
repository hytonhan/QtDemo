#include "programstudentrepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include "../../infra/databaseservice.h"

ProgramStudentRepository::ProgramStudentRepository(const QSqlDatabase& db)
    :db_(db)
{}

std::variant<std::vector<Student>, QString> ProgramStudentRepository::studentsForProgram(int programId) const
{
    QSqlQuery query(db_);
    const QString queryString = DatabaseService::loadSql(":/sql/sql/fetch_programstudents.sql");
    if (queryString.isEmpty()) {
        return QString("Couldn't sql command file or it was empty %1").arg(query.lastError().text());
    }
    query.prepare(queryString);
    query.bindValue(":program_id", programId);

    if (!query.exec()) {
        auto foo = query.lastError().text();
        return QString("Failed to fetch students of program %1").arg(query.lastError().text());
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

std::variant<std::vector<Student>, QString> ProgramStudentRepository::studentsNotInProgram(int programId) const
{
    QSqlQuery query(db_);
    const QString queryString = DatabaseService::loadSql(":/sql/sql/fetch_studentsnotinprogram.sql");
    if (queryString.isEmpty()) {
        return QString("Couldn't sql command file or it was empty %1").arg(query.lastError().text());
    }
    query.prepare(queryString);

    query.bindValue(":program_id", programId);

    if (!query.exec()) {
        auto lastError = query.lastError().text();
        return QString("Failed to fetch students not in program %1").arg(query.lastError().text());
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

std::variant<std::vector<Program>, QString> ProgramStudentRepository::programsForStudent(int studentId) const
{
    QSqlQuery query(db_);
    const QString queryString = DatabaseService::loadSql(":/sql/sql/fetch_studentprograms.sql");
    if (queryString.isEmpty()) {
        return QString("Couldn't sql command file or it was empty %1").arg(query.lastError().text());
    }
    query.prepare(queryString);
    query.bindValue(":student_id", studentId);
    if (!query.exec()) {
        auto lastError = query.lastError().text();
        return QString("Failed to fetch programs of student %1").arg(query.lastError().text());
    }

    std::vector<Program> programs;
    while(query.next()) {
        programs.emplace_back(query.value("id").toString(),
                              query.value("name").toString());
    }
    return programs;
}

std::optional<QString> ProgramStudentRepository::assignStudent(int programId, int studentId)
{
    QSqlQuery query(db_);
    const QString queryString = DatabaseService::loadSql(":/sql/sql/link_programstudent.sql");
    if (queryString.isEmpty()) {
        return QString("Couldn't sql command file or it was empty. %1").arg(query.lastError().text());
    }
    query.prepare(queryString);
    query.bindValue(":program_id", programId);
    query.bindValue(":student_id", studentId);

    if (!query.exec()) {
        return QString("Failed to link student to program %1").arg(query.lastError().text());
    }
    return std::nullopt;
}

std::optional<QString> ProgramStudentRepository::removeStudent(int programId, int studentId)
{
    QSqlQuery query(db_);
    const QString queryString = DatabaseService::loadSql(":/sql/sql/unlink_programstudent.sql");
    if (queryString.isEmpty()) {
        return QString("Couldn't sql command file or it was empty. %1").arg(query.lastError().text());
    }
    query.prepare(queryString);

    query.bindValue(":student_id", studentId);
    query.bindValue(":program_id", programId);

    if (!query.exec()) {
        return QString("Failed to unlink student into program %1").arg(query.lastError().text());
    }
    return std::nullopt;
}

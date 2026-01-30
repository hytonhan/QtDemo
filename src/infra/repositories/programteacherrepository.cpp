#include "programteacherrepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include "../../infra/databaseservice.h"

ProgramTeacherRepository::ProgramTeacherRepository(const QSqlDatabase& db) {}


std::variant<std::vector<Teacher>, QString> ProgramTeacherRepository::teachersForProgram(int programId) const
{
    QSqlQuery query(db_);
    const QString queryString = DatabaseService::loadSql(":/sql/sql/fetch_programteachers.sql");
    if (queryString.isEmpty()) {
        return QString("Couldn't sql command file or it was empty. %1").arg(query.lastError().text());
    }
    query.prepare(queryString);
    query.bindValue(":program_id", programId);

    if (!query.exec()) {
        auto foo = query.lastError().text();
        return QString("Failed to fetch teachers of program: %1").arg(query.lastError().text());
    }

    std::vector<Teacher> teachers;
    while(query.next()) {
        teachers.emplace_back(query.value("firstName").toString(),
                              query.value("lastName").toString(),
                              query.value("address").toString(),
                              query.value("phoneNumber").toString(),
                              query.value("id").toString(),
                              query.value("salary").toFloat(),
                              query.value("field").toString());
    }
    return teachers;
}

std::variant<std::vector<Teacher>, QString> ProgramTeacherRepository::teachersNotInProgram(int programId) const
{
    QSqlQuery query(db_);
    const QString queryString = DatabaseService::loadSql(":/sql/sql/fetch_teachersnotinprogram.sql");
    if (queryString.isEmpty()) {
        return QString("Couldn't sql command file or it was empty. %1").arg(query.lastError().text());
    }
    query.prepare(queryString);

    query.bindValue(":program_id", programId);

    if (!query.exec()) {
        auto lastError = query.lastError().text();
        return QString("Failed to fetch teachers not in program: %1").arg(query.lastError().text());
    }

    std::vector<Teacher> opettajat;
    while(query.next()) {
        opettajat.emplace_back(query.value("firstName").toString(),
                               query.value("lastName").toString(),
                               query.value("address").toString(),
                               query.value("phoneNumber").toString(),
                               query.value("id").toString(),
                               query.value("salary").toFloat(),
                               query.value("field").toString());
    }
    return opettajat;
}

std::variant<std::vector<Program>, QString> ProgramTeacherRepository::programsForTeacher(int teacherId) const
{
    QSqlQuery query(db_);
    const QString queryString = DatabaseService::loadSql(":/sql/sql/fetch_teacherprograms.sql");
    if (queryString.isEmpty()) {
        return QString("Couldn't sql command file or it was empty. %1").arg(query.lastError().text());
    }
    query.prepare(queryString);
    query.bindValue(":teacher_id", teacherId);
    if (!query.exec()) {
        auto lastError = query.lastError().text();
        return QString("Failed to fetch programs of teacher: %1").arg(query.lastError().text());
    }

    std::vector<Program> programs;

    while(query.next()) {
        programs.emplace_back(query.value("id").toString(),
                              query.value("name").toString());
    }
    return programs;
}

std::optional<QString> ProgramTeacherRepository::assignTeacher(int programId, int teacherId)
{
    QSqlQuery query(db_);
    const QString queryString = DatabaseService::loadSql(":/sql/sql/link_programteacher.sql");
    if (queryString.isEmpty()) {
        return QString("Couldn't sql command file or it was empty. %1").arg(query.lastError().text());
    }
    query.prepare(queryString);

    query.bindValue(":program_id", programId);
    query.bindValue(":teacher_id", teacherId);

    if (!query.exec()) {
        return QString("Failed to link teacher to program: %1").arg(query.lastError().text());
    }
    return std::nullopt;
}

std::optional<QString> ProgramTeacherRepository::removeTeacher(int programId, int teacherId)
{
    QSqlQuery query(db_);
    const QString queryString = DatabaseService::loadSql(":/sql/sql/unlink_programteacher.sql");
    if (queryString.isEmpty()) {
        return QString("Couldn't sql command file or it was empty. %1").arg(query.lastError().text());
    }
    query.prepare(queryString);

    query.bindValue(":teacher_id", teacherId);
    query.bindValue(":program_id", programId);

    if (!query.exec()) {
        return QString("Failed to unlink teacher and program: %1").arg(query.lastError().text());
    }
    return std::nullopt;
}

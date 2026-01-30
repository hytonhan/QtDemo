#include "programrepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "../databaseservice.h"

ProgramRepository::ProgramRepository(const QSqlDatabase& db)
    :db_(db)
{}

std::optional<QString> ProgramRepository::insertProgram(int schoolId, const Program& program)
{
    QSqlQuery query(db_);
    const QString queryString = DatabaseService::loadSql(":/sql/sql/insert_program.sql");
    if (queryString.isEmpty()) {
        return "Couldn't sql command file or it was empty.";
    }
    if (!query.prepare(queryString)) {
        return QString("Insert preparation failed: %1").arg(query.lastError().text());
    }
    query.bindValue(":name", program.name());
    query.bindValue(":school_id", schoolId);

    if (!query.exec()) {
        return QString("Failed to insert program: %1").arg(query.lastError().text());
    }
    return std::nullopt;
}

std::variant<std::vector<Program>, QString> ProgramRepository::getPrograms() const
{
    QSqlQuery query(db_);
    const QString queryString = DatabaseService::loadSql(":/sql/sql/fetch_programs.sql");
    if (queryString.isEmpty()) {
        return QString("Fetch command was empty or not found %1").arg(query.lastError().text());
    }
    if (!query.prepare(queryString)) {
        return QString("Query preparation failed %1").arg(query.lastError().text());
    }
    if (!query.exec()) {
        return QString("Failed to fetch programs %1").arg(query.lastError().text());
    }
    std::vector<Program> programs;
    while (query.next()) {
        programs.emplace_back(QString::number(query.value("id").toInt()),
                              query.value("name").toString());
    }
    return programs;
}

std::optional<QString> ProgramRepository::deleteProgram(int programId)
{
    QSqlQuery query(db_);
    const QString queryString = DatabaseService::loadSql(":/sql/sql/delete_program.sql");
    if (queryString.isEmpty()) {
        return "Delete command was empty or not found";
    }
    if (!query.prepare(queryString)) {
        return QString("Query preparation failed: %1").arg(query.lastError().text());
    }
    query.bindValue(":id", programId);
    if (!query.exec()) {
        return QString("Failed to delete program: %1").arg(query.lastError().text());
    }
    return std::nullopt;
}

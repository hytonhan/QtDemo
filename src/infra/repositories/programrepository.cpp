#include "programrepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include "../databaseservice.h"

ProgramRepository::ProgramRepository(QSqlDatabase db)
{
}

bool ProgramRepository::insertProgram(int schoolId, const Program& program)
{
    QSqlQuery query(db_);
    QString queryString = DatabaseService::loadSql(":/sql/sql/insert_program.sql");
    if (queryString.isEmpty()) {
        qCritical() << "Couldn't sql command file or it was empty.";
        return false;
    }
    if (!query.prepare(queryString)) {
        qCritical() << "Insert preparation failed:" << query.lastError().text();
        return false;
    }
    query.bindValue(":name", program.name());
    query.bindValue(":school_id", schoolId);

    if (!query.exec()) {
        qCritical() << "Failed to insert program:" << query.lastError().text();
        return false;
    }
    return true;
}

std::vector<Program> ProgramRepository::getPrograms() const
{
    std::vector<Program> programs;
    QSqlQuery query(db_);
    QString queryString = DatabaseService::loadSql(":/sql/sql/fetch_programs.sql");
    if (queryString.isEmpty()) {
        qCritical() << "Fetch command was empty or not found";
        return std::vector<Program>();
    }
    if (!query.prepare(queryString)) {
        qCritical() << "Query preparation failed:" << query.lastError().text();
        return std::vector<Program>();
    }
    if (!query.exec()) {
        qCritical() << "Failed to fetch programs" << query.lastError().text();
        return std::vector<Program>();
    }
    while (query.next()) {
        programs.emplace_back(QString::number(query.value("id").toInt()),
                              query.value("name").toString());
    }
    return programs;
}

bool ProgramRepository::deleteProgram(int programId)
{
    QSqlQuery query(db_);
    QString queryString = DatabaseService::loadSql(":/sql/sql/delete_program.sql");
    if (queryString.isEmpty()) {
        qCritical() << "Delete command was empty or not found";
        return false;
    }
    if (!query.prepare(queryString)) {
        qCritical() << "Query preparation failed:" << query.lastError().text();
        return false;
    }
    query.bindValue(":id", programId);
    if (!query.exec()) {
        qCritical() << "Failed to delete program" << query.lastError().text();
        return false;
    }
    return true;
}

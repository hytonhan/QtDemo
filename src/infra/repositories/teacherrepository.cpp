#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include "../databaseservice.h"
#include "teacherrepository.h"

TeacherRepository::TeacherRepository(const QSqlDatabase& db)
    :db_(db)
{}

std::optional<QString> TeacherRepository::insertTeacher(const Teacher& teacher)
{
    QSqlQuery query(db_);
    QString queryString = DatabaseService::loadSql(":/sql/sql/insert_teacher.sql");
    if (queryString.isEmpty()) {
        return QString("Couldn't sql command file or it was empty: %1").arg(query.lastError().text());
    }
    if (!query.prepare(queryString)) {
        return QString("Insert preparation failed: %1").arg(query.lastError().text());
    }
    query.bindValue(":firstName", teacher.firstName());
    query.bindValue(":lastName", teacher.lastName());
    query.bindValue(":address", teacher.address());
    query.bindValue(":phoneNumber", teacher.phoneNumber());
    query.bindValue(":field", teacher.field());
    query.bindValue(":salary", teacher.salary());

    if (!query.exec()) {
        return QString("Failed to insert teacher: %1").arg(query.lastError().text());
    }
    return std::nullopt;
}

std::variant<std::vector<Teacher>, QString> TeacherRepository::getTeachers() const
{
    std::vector<Teacher> teachers;
    QSqlQuery query(db_);
    QString queryString = DatabaseService::loadSql(":/sql/sql/fetch_teachers.sql");
    if (queryString.isEmpty()) {
        return QString("Fetch command was empty or not found: %1").arg(query.lastError().text());
    }
    if (!query.prepare(queryString)) {
        return QString("Query preparation failed: %1").arg(query.lastError().text());
    }
    if (!query.exec()) {
        return QString("Failed to fetch teachers: %1").arg(query.lastError().text());
    }
    while (query.next()) {
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

std::optional<QString> TeacherRepository::deleteTeacher(int teacherId)
{
    QString queryString = DatabaseService::loadSql(":/sql/sql/delete_teacher.sql");
    QSqlQuery query(db_);
    if (queryString.isEmpty()) {
        return QString("Delete command was empty or not found: %1").arg(query.lastError().text());
    }
    if (!query.prepare(queryString)) {
        return QString("Query preparation failed: %1").arg(query.lastError().text());
    }
    query.bindValue(":id", teacherId);
    if (!query.exec()) {
        return QString("Failed to delete teacher: %1").arg(query.lastError().text());
    }
    return std::nullopt;
}

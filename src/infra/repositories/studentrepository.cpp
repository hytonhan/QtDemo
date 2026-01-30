#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include "../databaseservice.h"
#include "studentrepository.h"

StudentRepository::StudentRepository(const QSqlDatabase& db)
    :db_(db)
{}

std::optional<QString> StudentRepository::insertStudent(const Student& student)
{
    QSqlQuery query(db_);
    QString queryString = DatabaseService::loadSql(":/sql/sql/insert_student.sql");
    if (queryString.isEmpty()) {
        return QString("Couldn't sql command file or it was empty:  %1").arg(query.lastError().text());
    }
    if (!query.prepare(queryString)) {
        return QString("Insert preparation failed: %1").arg(query.lastError().text());
    }
    query.bindValue(":firstName", student.firstName());
    query.bindValue(":lastName", student.lastName());
    query.bindValue(":address", student.address());
    query.bindValue(":phoneNumber", student.phoneNumber());

    if (!query.exec()) {
        return QString("Failed to insert student: %1").arg(query.lastError().text());
    }
    return std::nullopt;
}

std::variant<std::vector<Student>, QString> StudentRepository::getStudents() const
{
    std::vector<Student> students;
    QSqlQuery query(db_);
    QString queryString = DatabaseService::loadSql(":/sql/sql/fetch_students.sql");
    if (queryString.isEmpty()) {
        return QString("Fetch command was empty or not found: %1").arg(query.lastError().text());
    }
    if (!query.prepare(queryString)) {
        return QString("Query preparation failed: %1").arg(query.lastError().text());
    }
    if (!query.exec()) {
        return QString("Failed to fetch students: %1").arg(query.lastError().text());
    }
    while (query.next()) {
        students.emplace_back(query.value("firstName").toString(),
                              query.value("lastName").toString(),
                              query.value("address").toString(),
                              query.value("phoneNumber").toString(),
                              query.value("id").toString());
    }
    return students;
}

std::optional<QString> StudentRepository::deleteStudent(const Student& student)
{
    QString queryString = DatabaseService::loadSql(":/sql/sql/delete_student.sql");
    QSqlQuery query(db_);
    if (queryString.isEmpty()) {
        return QString("Delete command was empty or not found: %1").arg(query.lastError().text());
    }
    if (!query.prepare(queryString)) {
        return QString("Query preparation failed: %1").arg(query.lastError().text());
    }
    query.bindValue(":id", student.id());
    if (!query.exec()) {
        return QString("Failed to delete student: %1").arg(query.lastError().text());
    }
    return std::nullopt;
}

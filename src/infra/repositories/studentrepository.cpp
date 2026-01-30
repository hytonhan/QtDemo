#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include "../databaseservice.h"
#include "studentrepository.h"

StudentRepository::StudentRepository(const QSqlDatabase& db) {}

bool StudentRepository::insertStudent(const Student& student)
{
    QSqlQuery query(db_);
    QString queryString = DatabaseService::loadSql(":/sql/sql/insert_student.sql");
    if (queryString.isEmpty()) {
        qCritical() << "Couldn't sql command file or it was empty.";
        return false;
    }
    if (!query.prepare(queryString)) {
        qCritical() << "Insert preparation failed:" << query.lastError().text();
        return false;
    }
    query.bindValue(":firstName", student.firstName());
    query.bindValue(":lastName", student.lastName());
    query.bindValue(":address", student.address());
    query.bindValue(":phoneNumber", student.phoneNumber());

    if (!query.exec()) {
        qCritical() << "Failed to insert student:" << query.lastError().text();
        return false;
    }
    return true;
}

std::vector<Student> StudentRepository::getStudents() const
{
    std::vector<Student> students;
    QSqlQuery query(db_);
    QString queryString = DatabaseService::loadSql(":/sql/sql/fetch_students.sql");
    if (queryString.isEmpty()) {
        qCritical() << "Fetch command was empty or not found";
        return std::vector<Student>();
    }
    if (!query.prepare(queryString)) {
        qCritical() << "Query preparation failed:" << query.lastError().text();
        return std::vector<Student>();
    }
    if (!query.exec()) {
        qCritical() << "Failed to fetch students:" << query.lastError().text();
        return std::vector<Student>();
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

bool StudentRepository::deleteStudent(const Student& student)
{
    QString queryString = DatabaseService::loadSql(":/sql/sql/delete_student.sql");
    QSqlQuery query(db_);
    if (queryString.isEmpty()) {
        qCritical() << "Delete command was empty or not found";
        return false;
    }
    if (!query.prepare(queryString)) {
        qCritical() << "Query preparation failed:" << query.lastError().text();
        return false;
    }
    query.bindValue(":id", student.id());
    if (!query.exec()) {
        qCritical() << "Failed to delete student:" << query.lastError().text();
        return false;
    }
    return true;
}

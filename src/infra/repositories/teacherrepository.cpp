#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include "../databaseservice.h"
#include "teacherrepository.h"

TeacherRepository::TeacherRepository(const QSqlDatabase& db)
{}

bool TeacherRepository::insertTeacher(const Teacher& teacher)
{
    QSqlQuery query(db_);
    QString queryString = DatabaseService::loadSql(":/sql/sql/insert_teacher.sql");
    if (queryString.isEmpty()) {
        qCritical() << "Couldn't sql command file or it was empty.";
        return false;
    }
    if (!query.prepare(queryString)) {
        qCritical() << "Insert preparation failed:" << query.lastError().text();
        return false;
    }
    query.bindValue(":firstName", teacher.firstName());
    query.bindValue(":lastName", teacher.lastName());
    query.bindValue(":address", teacher.address());
    query.bindValue(":phoneNumber", teacher.phoneNumber());
    query.bindValue(":field", teacher.field());
    query.bindValue(":salary", teacher.salary());

    if (!query.exec()) {
        qCritical() << "Failed to insert teacher:" << query.lastError().text();
        return false;
    }
    return true;
}

std::vector<Teacher> TeacherRepository::getTeachers() const
{
    std::vector<Teacher> teachers;
    QSqlQuery query(db_);
    QString queryString = DatabaseService::loadSql(":/sql/sql/fetch_teachers.sql");
    if (queryString.isEmpty()) {
        qCritical() << "Fetch command was empty or not found";
        return std::vector<Teacher>();
    }
    if (!query.prepare(queryString)) {
        qCritical() << "Query preparation failed:" << query.lastError().text();
        return std::vector<Teacher>();
    }
    if (!query.exec()) {
        qCritical() << "Failed to fetch teachers:" << query.lastError().text();
        return std::vector<Teacher>();
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

bool TeacherRepository::deleteTeacher(int teacherId)
{
    QString queryString = DatabaseService::loadSql(":/sql/sql/delete_teacher.sql");
    QSqlQuery query(db_);
    if (queryString.isEmpty()) {
        qCritical() << "Delete command was empty or not found";
        return false;
    }
    if (!query.prepare(queryString)) {
        qCritical() << "Query preparation failed:" << query.lastError().text();
        return false;
    }
    query.bindValue(":id", teacherId);
    if (!query.exec()) {
        qCritical() << "Failed to delete teacher:" << query.lastError().text();
        return false;
    }
    return true;
}

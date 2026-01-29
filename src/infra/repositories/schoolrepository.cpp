#include "schoolrepository.h"
#include <QSqlQuery>
#include <QSqlError>

SchoolRepository::SchoolRepository(QSqlDatabase db)
{}

School SchoolRepository::getSchool() const
{
    School school;
    QSqlQuery query(db_);
    if (!query.prepare("SELECT id, name FROM school WHERE id = 1"))
    {
        qCritical() << "Query preparation failed";
        return school;
    }
    if (!query.exec()) {
        qCritical() << "Failed to get School:" << query.lastError().text();
        return school;
    }
    if (query.next()) {
        return School(QString(query.value("id").toString()),
                      QString(query.value("name").toString()));
    } else {
        qWarning() << "No School found with id = 1";
    }

    return school;
}

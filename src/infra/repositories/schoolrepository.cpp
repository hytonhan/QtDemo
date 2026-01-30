#include "schoolrepository.h"
#include <QSqlQuery>
#include <QSqlError>

SchoolRepository::SchoolRepository(const QSqlDatabase& db)
    : db_(db)
{}

std::optional<School> SchoolRepository::getSchool(int id) const
{
    QSqlQuery query(db_);
    if (!query.prepare("SELECT id, name FROM school WHERE id = :id"))
    {
        qCritical() << "Failed to prepare school query:";
        return std::nullopt;
    }
    query.bindValue(":id", id);
    if (!query.exec()) {
        qCritical() << "Failed to execute school query:" << query.lastError().text();
        return std::nullopt;
    }
    if (!query.next()) {
        qWarning() << "No school found with id =" << id;
        return std::nullopt;
    }

    return School(
        query.value("id").toString(),
        query.value("name").toString()
        );
}

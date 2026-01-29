#ifndef SCHOOLREPOSITORY_H
#define SCHOOLREPOSITORY_H
#include <QString>
#include <QSqlDatabase>
#include "../../domain/school.h"

class SchoolRepository
{
public:
    explicit SchoolRepository(QSqlDatabase db);

    School getSchool() const;
private:
    QSqlDatabase db_;
};

#endif // SCHOOLREPOSITORY_H

#include "programteacherrepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include "../../infra/databaseservice.h"

ProgramTeacherRepository::ProgramTeacherRepository(QSqlDatabase db) {}


std::vector<Teacher> ProgramTeacherRepository::teachersForProgram(int programId)
{
    QSqlQuery query(db_);

    QString queryString = DatabaseService::loadSql(":/sql/sql/fetch_programteachers.sql");
    if (queryString.isEmpty()) {
        qCritical() << "Couldn't sql command file or it was empty.";
        return std::vector<Teacher>();
    }
    query.prepare(queryString);
    query.bindValue(":program_id", programId);

    if (!query.exec()) {
        auto foo = query.lastError().text();
        qCritical() << "Failed to fetch teachers of program:" << query.lastError().text();
        return std::vector<Teacher>();
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

std::vector<Teacher> ProgramTeacherRepository::teachersNotInProgram(int programId)
{
    QSqlQuery query(db_);
    QString queryString = DatabaseService::loadSql(":/sql/sql/fetch_teachersnotinprogram.sql");
    if (queryString.isEmpty()) {
        qCritical() << "Couldn't sql command file or it was empty.";
        return std::vector<Teacher>();
    }
    query.prepare(queryString);

    query.bindValue(":program_id", programId);

    if (!query.exec()) {
        auto lastError = query.lastError().text();
        qCritical() << "Failed to fetch teachers not in program:" << query.lastError().text();
        return std::vector<Teacher>();
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

std::vector<Program> ProgramTeacherRepository::programsForTeacher(int teacherId)
{
    QSqlQuery query(db_);
    QString queryString = DatabaseService::loadSql(":/sql/sql/fetch_teacherprograms.sql");
    if (queryString.isEmpty()) {
        qCritical() << "Couldn't sql command file or it was empty.";
        return std::vector<Program>();
    }
    query.prepare(queryString);
    query.bindValue(":teacher_id", teacherId);
    if (!query.exec()) {
        auto lastError = query.lastError().text();
        qCritical() << "Failed to fetch programs of teacher" << query.lastError().text();
        return std::vector<Program>();
    }

    std::vector<Program> programs;

    while(query.next()) {
        programs.emplace_back(query.value("id").toString(),
                              query.value("name").toString());
    }
    return programs;
}

void ProgramTeacherRepository::assignTeacher(int programId, int teacherId)
{
    QSqlQuery query(db_);
    QString queryString = DatabaseService::loadSql(":/sql/sql/link_programteacher.sql");
    if (queryString.isEmpty()) {
        qCritical() << "Couldn't sql command file or it was empty.";
        return;
    }
    query.prepare(queryString);

    query.bindValue(":program_id", programId);
    query.bindValue(":teacher_id", teacherId);

    if (!query.exec()) {
        qCritical() << "Failed to link teacher to program:"
                    << query.lastError().text();
        return;
    }
    return;
}

void ProgramTeacherRepository::removeTeacher(int programId, int teacherId)
{
    QSqlQuery query(db_);
    QString queryString = DatabaseService::loadSql(":/sql/sql/unlink_programteacher.sql");
    if (queryString.isEmpty()) {
        qCritical() << "Couldn't sql command file or it was empty.";
        return;
    }
    query.prepare(queryString);

    query.bindValue(":teacher_id", teacherId);
    query.bindValue(":program_id", programId);

    if (!query.exec()) {
        qCritical() << "Failed to unlink teacher and program:" << query.lastError().text();
        return;
    }
    return;
}

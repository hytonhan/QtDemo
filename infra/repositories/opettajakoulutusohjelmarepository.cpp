#include "opettajakoulutusohjelmarepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include <vector>

OpettajaKoulutusOhjelmaRepository::OpettajaKoulutusOhjelmaRepository(QSqlDatabase db)
    : EntiteettiKoulutusOhjelmaRepository(db)
{}

std::vector<Program> OpettajaKoulutusOhjelmaRepository::fetchAssignedPrograms(int entityId)
{
    QSqlQuery query(db_);
    query.prepare(
        "SELECT p.id, p.name "
        "FROM program AS p "
        "INNER JOIN program_teacher ON p.id = program_teacher.program_id "
        "WHERE program_teacher.teacher_id = :teacher_id");

    query.bindValue(":teacher_id", entityId);

    if (!query.exec()) {
        auto foo = query.lastError().text();
        qCritical() << "Failed to fetch koulutusohjelmat for teacher" << query.lastError().text();
        return std::vector<Program>();
    }

    std::vector<Program> programs;
    while(query.next()) {
        Program ko(query.value("id").toString(),
                           query.value("name").toString());
        programs.push_back(ko);
    }
    return programs;
}

std::vector<Program> OpettajaKoulutusOhjelmaRepository::fetchAvailablePrograms(int entityId)
{
    QSqlQuery query(db_);
    query.prepare(
        "SELECT p.id, p.name "
        "FROM program AS p "
        "WHERE NOT EXISTS ( "
        "SELECT 1 "
        "FROM program_teacher "
        "WHERE program_teacher.teacher_id = :teacher.id "
        "AND program_teacher.program_id = p.id "
        ");"
        );
    query.bindValue(":teacher.id", entityId);
    if (!query.exec()) {
        auto lastError = query.lastError().text();
        qCritical() << "Failed to fetch koulutusohjelmat for teacher:" << query.lastError().text();
        return std::vector<Program>();
    }

    std::vector<Program> koulutusohjelmat;
    while(query.next()) {
        Program ko(query.value("id").toString(),
                           query.value("name").toString());
        koulutusohjelmat.push_back(ko);
    }
    return koulutusohjelmat;
}

void OpettajaKoulutusOhjelmaRepository::addProgram(int entityId, int programId)
{
    QSqlQuery query(db_);
    query.prepare(
        "INSERT INTO program_teacher (program_id, teacher_id) "
        "VALUES (:program_id, :teacher_id)"
        );

    query.bindValue(":program_id", programId);
    query.bindValue(":teacher_id", entityId);

    if (!query.exec()) {
        qCritical() << "Failed to link teacher to koulutusohjelma:"
                    << query.lastError().text();
        return;
    }
    return;
}

void OpettajaKoulutusOhjelmaRepository::removeProgram(int entityId, int programId)
{
    QSqlQuery query(db_);
    query.prepare(
        "DELETE FROM program_teacher "
        "WHERE teacher_id = :teacher_id AND program_id = :program_id");

    query.bindValue(":teacher_id", entityId);
    query.bindValue(":program_id", programId);

    if (!query.exec()) {
        qCritical() << "Failed to unlink teacher and koulutusohjelma:" << query.lastError().text();
        return;
    }
    return;
}

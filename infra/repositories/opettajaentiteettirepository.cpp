#include "opettajaentiteettirepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include <vector>
#include "../adapters/opettajaadapter.h"
#include "../domain/teacher.h"

OpettajaEntiteettiRepository::OpettajaEntiteettiRepository(QSqlDatabase db)
    : KoulutusOhjelmanEntiteettiRepository(db)
{}

std::vector<std::unique_ptr<KoulutusOhjelmanEntiteetti>> OpettajaEntiteettiRepository::fetchAvailable(int programId)
{
    QSqlQuery query(db_);
    query.prepare(
        "SELECT firstName, lastName, address, phoneNumber, id, salary, field "
        "FROM teacher "
        "WHERE NOT EXISTS ( "
        "SELECT 1 "
        "FROM program_teacher "
        "WHERE program_teacher.teacher_id = teacher.id "
        "AND program_teacher.program_id = :program_id "
        ");"
        );

    query.bindValue(":program_id", programId);

    if (!query.exec()) {
        auto lastError = query.lastError().text();
        qCritical() << "Failed to fetch opettajat not in koulutusohjelma:" << query.lastError().text();
        return std::vector<std::unique_ptr<KoulutusOhjelmanEntiteetti>>();
    }

    std::vector<std::unique_ptr<KoulutusOhjelmanEntiteetti>> opettajat;
    while(query.next()) {
        Teacher ope(query.value("firstName").toString(),
                     query.value("lastName").toString(),
                     query.value("address").toString(),
                     query.value("phoneNumber").toString(),
                     query.value("id").toString(),
                     query.value("salary").toFloat(),
                     query.value("field").toString());
        auto ptr = std::unique_ptr<KoulutusOhjelmanEntiteetti>(new OpettajaAdapter(ope));
        opettajat.push_back(std::move(ptr));
    }
    return opettajat;
}

std::vector<std::unique_ptr<KoulutusOhjelmanEntiteetti>> OpettajaEntiteettiRepository::fetchAssigned(int programId)
{
    QSqlQuery query(db_);
    query.prepare(
        "SELECT firstName, lastName, address, phoneNumber, id, salary, field "
        "FROM teacher "
        "INNER JOIN program_teacher ON teacher.id = program_teacher.teacher_id "
        "WHERE program_teacher.program_id = :program_id");

    query.bindValue(":program_id", programId);

    if (!query.exec()) {
        auto foo = query.lastError().text();
        qCritical() << "Failed to fetch opettajat of koulutusohjelma:" << query.lastError().text();
        return std::vector<std::unique_ptr<KoulutusOhjelmanEntiteetti>>();
    }

    std::vector<std::unique_ptr<KoulutusOhjelmanEntiteetti>> opettajat;
    while(query.next()) {
        Teacher ope(query.value("firstName").toString(),
                     query.value("lastName").toString(),
                     query.value("address").toString(),
                     query.value("phoneNumber").toString(),
                     query.value("id").toString(),
                     query.value("salary").toFloat(),
                     query.value("field").toString());
        auto ptr = std::unique_ptr<KoulutusOhjelmanEntiteetti>(new OpettajaAdapter(ope));
        opettajat.push_back(std::move(ptr));
        // opettajat.append(std::make_unique<OpettajaAdapter>(ope));
    }
    return opettajat;
}

void OpettajaEntiteettiRepository::add(int teacherId, int programId)
{
    QSqlQuery query(db_);
    query.prepare(
        "INSERT INTO program_teacher (program_id, teacher_id) "
        "VALUES (:program_id, :teacher_id)"
        );

    query.bindValue(":program_id", programId);
    query.bindValue(":teacher_id", teacherId);

    if (!query.exec()) {
        qCritical() << "Failed to link teacher to koulutusohjelma:"
                    << query.lastError().text();
        return;
    }
    return;
}

void OpettajaEntiteettiRepository::remove(int teacherId, int programId)
{
    QSqlQuery query(db_);
    query.prepare(
        "DELETE FROM program_teacher "
        "WHERE teacher_id = :teacher_id AND program_id = :program_id");

    query.bindValue(":teacher_id", teacherId);
    query.bindValue(":program_id", programId);

    if (!query.exec()) {
        qCritical() << "Failed to unlink teacher and koulutusohjelma:" << query.lastError().text();
        return;
    }
    return;
}

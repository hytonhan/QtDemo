#include "opiskelijaentiteettirepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include "../adapters/opiskelijaadapter.h"
#include "../domain/student.h"

OpiskelijaEntiteettiRepository::OpiskelijaEntiteettiRepository(QSqlDatabase db)
    : KoulutusOhjelmanEntiteettiRepository(db)
{}

std::vector<std::unique_ptr<KoulutusOhjelmanEntiteetti>> OpiskelijaEntiteettiRepository::fetchAvailable(int programId)
{
    QSqlQuery query(db_);
    query.prepare(
        "SELECT firstName, lastName, address, phoneNumber, id "
        "FROM student "
        "WHERE NOT EXISTS ( "
        "SELECT 1 "
        "FROM program_student "
        "WHERE program_student.student_id = student.id "
        "AND program_student.program_id = :program_id "
        ");"
        );

    query.bindValue(":program_id", programId);

    if (!query.exec()) {
        auto lastError = query.lastError().text();
        qCritical() << "Failed to fetch opiskelijat not in koulutusohjelma:" << query.lastError().text();
        return std::vector<std::unique_ptr<KoulutusOhjelmanEntiteetti>>();
    }

    std::vector<std::unique_ptr<KoulutusOhjelmanEntiteetti>> opiskelijat;
    while(query.next()) {
        Student opisk(query.value("firstName").toString(),
                         query.value("lastName").toString(),
                         query.value("address").toString(),
                         query.value("phoneNumber").toString(),
                         query.value("id").toString());
        opiskelijat.push_back(std::make_unique<OpiskelijaAdapter>(opisk));
    }
    return opiskelijat;
}

std::vector<std::unique_ptr<KoulutusOhjelmanEntiteetti>> OpiskelijaEntiteettiRepository::fetchAssigned(int programId)
{
    QSqlQuery query(db_);
    query.prepare(
        "SELECT firstName, lastName, address, phoneNumber, id "
        "FROM student "
        "INNER JOIN program_student ON student.id = program_student.student_id "
        "WHERE program_student.program_id = :program_id");

    query.bindValue(":program_id", programId);

    if (!query.exec()) {
        auto foo = query.lastError().text();
        qCritical() << "Failed to fetch opiskelijat of koulutusohjelma:" << query.lastError().text();
        return std::vector<std::unique_ptr<KoulutusOhjelmanEntiteetti>>();
    }

    std::vector<std::unique_ptr<KoulutusOhjelmanEntiteetti>> opiskelijat;
    while(query.next()) {
        Student opisk(query.value("firstName").toString(),
                         query.value("lastName").toString(),
                         query.value("address").toString(),
                         query.value("phoneNumber").toString(),
                         query.value("id").toString());
        opiskelijat.push_back(std::make_unique<OpiskelijaAdapter>(opisk));
    }
    return opiskelijat;
}

void OpiskelijaEntiteettiRepository::add(int studentId, int programId)
{
    QSqlQuery query(db_);
    query.prepare(
        "INSERT INTO program_student (program_id, student_id) "
        "VALUES (:program_id, :student_id)"
        );

    query.bindValue(":program_id", programId);
    query.bindValue(":student_id", studentId);

    if (!query.exec()) {
        qCritical() << "Failed to link student to koulutusohjelma:"
                    << query.lastError().text();
        return;
    }
    return;
}

void OpiskelijaEntiteettiRepository::remove(int studentId, int programId)
{
    QSqlQuery query(db_);
    query.prepare(
        "DELETE FROM program_student "
        "WHERE student_id = :student_id AND program_id = :program_id");

    query.bindValue(":student_id", studentId);
    query.bindValue(":program_id", programId);

    if (!query.exec()) {
        qCritical() << "Failed to unlink student and koulutusohjelma:" << query.lastError().text();
        return;
    }
    return;
}

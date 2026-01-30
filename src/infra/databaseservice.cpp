#include "databaseservice.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QStandardPaths>
#include <QSqlQuery>
#include <QFile>
#include <QIODevice>
#include <QString>
#include <QDir>

DatabaseService::DatabaseService() {}

DatabaseService::~DatabaseService()
{
    if (db_.isOpen()) {
        db_.close();
    }
}

DatabaseService& DatabaseService::instance()
{
    static DatabaseService _instance;
    return _instance;
}

QSqlDatabase DatabaseService::database() const
{
    return db_;
}

QString DatabaseService::loadSql(const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return QString();
    return QString::fromUtf8(file.readAll());
}


std::optional<QString> DatabaseService::openDatabase(QString name)
{
    db_ = QSqlDatabase::addDatabase("QSQLITE");
    if (name == ":memory:") {
        db_.setDatabaseName(name);
    }
    else {
        QString dbDirectory = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        QDir().mkpath(dbDirectory);
        QString location = dbDirectory + "/" + name;
        db_.setDatabaseName(location);
    }

    if (!db_.open()) {
        return QString("Database open failed: %1").arg(db_.lastError().text());
    }

    return std::nullopt;
}

void DatabaseService::resetConnection()
{
    QString connectionName = db_.connectionName();
    db_ = QSqlDatabase();
    QSqlDatabase::removeDatabase(connectionName);
}

std::optional<QString> DatabaseService::initializeSchema()
{
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON");
    QString schemaSql = loadSql(QString::fromStdString(":/sql/sql/schema.sql"));
    if (schemaSql.isEmpty()) {
        return QString("Couldn't find database init file or it was empty: %1").arg(query.lastError().text());
    }

    for (const QString& statement : schemaSql.split(";", Qt::SkipEmptyParts)) {
        if (statement.trimmed().isEmpty())
            continue;
        if (!query.exec(statement.trimmed())) {
            return QString("SQL error: %1\nStatement: %2").arg(query.lastError().text(), statement);
        }
    }

    return std::nullopt;
}

std::optional<QString> DatabaseService::populateInitialData()
{
    QSqlQuery query;
    QString initialDataQuery = loadSql(QString::fromStdString(":/sql/sql/initial_data.sql"));
    if (initialDataQuery.isEmpty()) {
        return QString("Couldn't find database initial data file or it was empty. %1").arg(query.lastError().text());
    }
    for (const QString& statement : initialDataQuery.split(";", Qt::SkipEmptyParts)) {
        if (statement.trimmed().isEmpty())
            continue;
        if (!query.exec(statement)) {
            return QString("SQL error:  %1\nQuery: %2").arg(query.lastError().text(), statement);
        }
    }
    return std::nullopt;
}

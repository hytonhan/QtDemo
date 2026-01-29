#ifndef DATABASESERVICE_H
#define DATABASESERVICE_H

#include <QString>
#include <QSqlDatabase>

class DatabaseService
{
public:
    static DatabaseService& instance();
    QSqlDatabase database() const;
    bool openDatabase(QString name);
    bool populateInitialData();
    bool initializeSchema();
    void resetConnection();
    static QString loadSql(const QString& path);
private:
    DatabaseService();
    ~DatabaseService();
    DatabaseService(const DatabaseService&) = delete;
    DatabaseService& operator=(const DatabaseService&) = delete;

    QSqlDatabase db_;
};

#endif // DATABASESERVICE_H

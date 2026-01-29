#include <QtTest>
#include <QSqlQuery>
#include "../../src/infra/databaseservice.h"

class TestDatabaseService : public QObject
{
    Q_OBJECT

private slots:

    void init();
    void databaseOpensAndSchemaCreated();
};

void TestDatabaseService::init()
{
    Q_INIT_RESOURCE(resources);
}

void TestDatabaseService::databaseOpensAndSchemaCreated()
{
    DatabaseService& dbService = DatabaseService::instance();
    dbService.openDatabase(":memory:");
    dbService.initializeSchema();

    QSqlDatabase db = dbService.database();
    QVERIFY(db.isOpen());

    QSqlQuery query(db);
    QVERIFY(query.exec("SELECT name FROM sqlite_master WHERE type='table'"));
    QVERIFY(query.next());
}

QTEST_MAIN(TestDatabaseService)
#include "test_databaseservice.moc"

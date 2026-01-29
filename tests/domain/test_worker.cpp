#include <QtTest>
#include "../../src/domain/worker.h"

class TestWorker : public QObject
{
    Q_OBJECT

private slots:
    void workerSetsSalaryCorrectly();
};

void TestWorker::workerSetsSalaryCorrectly()
{
    Worker w("Firstname", "Lastname", "", "", "worker-1", 3500.0f);

    QCOMPARE(w.salary(), 3500.0f);
    QCOMPARE(w.fullName(), QString("Firstname Lastname"));
}

QTEST_MAIN(TestWorker)
#include "test_worker.moc"

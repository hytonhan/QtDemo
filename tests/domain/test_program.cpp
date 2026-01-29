#include <QtTest>
#include "../../src/domain/program.h"

class TestProgram : public QObject
{
    Q_OBJECT

private slots:
    void constructorSetsAllFields();
};

void TestProgram::constructorSetsAllFields()
{
    Program p("prog-1", "Ohjelmointi");

    QCOMPARE(p.id(), QString("prog-1"));
    QCOMPARE(p.name(), QString("Ohjelmointi"));
}

QTEST_MAIN(TestProgram)
#include "test_program.moc"

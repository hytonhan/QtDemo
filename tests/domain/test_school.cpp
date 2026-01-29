#include <QtTest>
#include "../../src/domain/school.h"

class TestSchool : public QObject
{
    Q_OBJECT

private slots:
    void constructorSetsAllFields();
};

void TestSchool::constructorSetsAllFields()
{
    School s("1", "TAMK");

    QCOMPARE(s.id(), QString("1"));
    QCOMPARE(s.name(), QString("TAMK"));
}

QTEST_MAIN(TestSchool)
#include "test_school.moc"

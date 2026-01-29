#include <QtTest>
#include "../../src/domain/teacher.h"

class TestTeacher : public QObject
{
    Q_OBJECT

private slots:
    void constructorSetsAllFields();
    void fullNameIsCombinedCorrectly();
};

void TestTeacher::constructorSetsAllFields()
{
    Teacher t("Firstname", "lastname", "address", "phonenumber", "id", 1234.0, "field");

    QCOMPARE(t.firstName(), QString("Firstname"));
    QCOMPARE(t.lastName(), QString("lastname"));
    QCOMPARE(t.address(), QString("address"));
    QCOMPARE(t.phoneNumber(), QString("phonenumber"));
    QCOMPARE(t.salary(), 1234.0);
    QCOMPARE(t.id(), QString("id"));
    QCOMPARE(t.field(), QString("field"));
}

void TestTeacher::fullNameIsCombinedCorrectly()
{
    Teacher t("Firstname", "lastname", "", "", "", 0, "");
    QVERIFY(t.fullName() == "Firstname lastname");
}


QTEST_MAIN(TestTeacher)
#include "test_teacher.moc"

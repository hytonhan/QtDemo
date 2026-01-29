#include <QtTest>
#include "../../src/domain/person.h"

class TestPerson : public QObject
{
    Q_OBJECT

private slots:
    void constructorSetsAllFields();
    void fullNameIsCombinedCorrectly();
};

void TestPerson::constructorSetsAllFields()
{
    Person p("Firstname", "Lastname", "address", "12345", "id-1");

    QCOMPARE(p.firstName(), QString("Firstname"));
    QCOMPARE(p.lastName(), QString("Lastname"));
    QCOMPARE(p.address(), QString("address"));
    QCOMPARE(p.phoneNumber(), QString("12345"));
    QCOMPARE(p.id(), QString("id-1"));
}

void TestPerson::fullNameIsCombinedCorrectly()
{
    Person p("Firstname", "Lastname", "", "", "");
    QCOMPARE(p.fullName(), QString("Firstname Lastname"));
}

QTEST_MAIN(TestPerson)
#include "test_person.moc"

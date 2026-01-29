#include <QtTest>
#include "../../src/domain/student.h"

class TestStudent : public QObject
{
    Q_OBJECT

private slots:
    void constructorSetsAllFields();
    void fullNameIsCombinedCorrectly();
};

void TestStudent::constructorSetsAllFields()
{
    Student s("Firstname", "Lastname", "address", "12345", "id-1");

    QCOMPARE(s.firstName(), QString("Firstname"));
    QCOMPARE(s.lastName(), QString("Lastname"));
    QCOMPARE(s.address(), QString("address"));
    QCOMPARE(s.phoneNumber(), QString("12345"));
    QCOMPARE(s.id(), QString("id-1"));
}

void TestStudent::fullNameIsCombinedCorrectly()
{
    Person p("Firstname", "Lastname", "", "", "");
    QCOMPARE(p.fullName(), QString("Firstname Lastname"));
}

QTEST_MAIN(TestStudent)
#include "test_student.moc"

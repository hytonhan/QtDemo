#include "infra/repositories/programrepository.h"
#include "infra/repositories/programstudentrepository.h"
#include "infra/repositories/programteacherrepository.h"
#include "infra/repositories/teacherrepository.h"
#include "services/programservice.h"
#include "services/programstudentassociationservice.h"
#include "services/programteacherassociationservice.h"
#include "services/teacherservice.h"
#include "ui/mainwindow.h"
#include "infra/databaseservice.h"
#include <QApplication>
#include "infra/repositories/schoolrepository.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DatabaseService& dbService = DatabaseService::instance();

    if (!dbService.openDatabase("school.db"))
        return -1;
    if (!dbService.initializeSchema())
        return -1;
    if (!dbService.populateInitialData())
        return -1;
    const QSqlDatabase db = dbService.database();

    SchoolRepository schoolRepo(db);
    ProgramRepository programRepo(db);
    TeacherRepository teacherRepo(db);
    ProgramTeacherRepository programTeacherRepo(db);
    ProgramStudentRepository programStudentRepo(db);

    ProgramService programService(programRepo);
    TeacherService teacherService(teacherRepo);
    ProgramTeacherAssociationService programTeacherService(programTeacherRepo);
    ProgramStudentAssociationService programStudentService(programStudentRepo);

    constexpr int DefaultSchoolId = 1;
    auto schoolOpt = schoolRepo.getSchool(DefaultSchoolId);
    if (!schoolOpt) {
        qCritical() << "Unable to load school";
        QMessageBox::critical(nullptr,
                              QObject::tr("Startup Error"),
                              QObject::tr("The application could not load required data."));

        return EXIT_FAILURE;
    }
    const School& school = *schoolOpt;

    MainWindow w(
        school,
        programService,
        teacherService,
        programTeacherService,
        programStudentService);
    w.show();
    return a.exec();
}

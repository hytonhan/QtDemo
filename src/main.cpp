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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DatabaseService& dbService = DatabaseService::instance();

    if (!dbService.openDatabase("koulu2.db"))
        return -1;
    if (!dbService.initializeSchema())
        return -1;
    if (!dbService.populateInitialData())
        return -1;
    QSqlDatabase db = dbService.database();

    SchoolRepository schoolRepo(db);
    ProgramRepository programRepo(db);
    TeacherRepository teacherRepo(db);
    ProgramTeacherRepository programTeacherRepo(db);
    ProgramStudentRepository programStudentRepo(db);

    ProgramService programService(programRepo);
    TeacherService teacherService(teacherRepo);
    ProgramTeacherAssociationService programTeacherService(programTeacherRepo);
    ProgramStudentAssociationService programStudentService(programStudentRepo);

    School school = schoolRepo.getSchool();

    MainWindow w(
        &school,
        programService,
        teacherService,
        programTeacherService,
        programStudentService);
    w.show();
    return a.exec();
}

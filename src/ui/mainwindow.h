#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include "../domain/school.h"
#include "../model/programlistmodel.h"
#include "../model/programteacherlistmodel.h"
#include "../model/programstudentlistmodel.h"
#include "../model/teacherlistmodel.h"
#include "../model/teacherprogramlistmodel.h"
#include "../services/programservice.h"
#include "../services/programstudentassociationservice.h"
#include "../services/programteacherassociationservice.h"
#include "../services/teacherservice.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(
        School& school,
        ProgramService& programService,
        TeacherService& teacherService,
        ProgramTeacherAssociationService& programTeacherService,
        ProgramStudentAssociationService& programStudentService,
        QWidget* parent = nullptr);
    ~MainWindow();
private:
    School& school_;
    Ui::MainWindow* ui_;

    ProgramListModel* programModel_;
    ProgramTeacherListModel* programTeacherModel_;
    ProgramStudentListModel* programStudentModel_;
    TeachersListModel* teacherModel_;
    TeacherProgramListModel* teacherProgramModel_;

    ProgramService& programService_;
    TeacherService& teacherService_;
    ProgramTeacherAssociationService& programTeacherService_;
    ProgramStudentAssociationService& programStudentService_;

private:
    void updateProgramCount();
    void updateOpettajatCount();
private slots:
    void onItemDoubleClicked(const QModelIndex& index);
    void onItemClicked(const QModelIndex& index);
    void onRemoveProgramClicked();
    void onAddTeacherToProgramClicked();
    void onRemoveTeacherFromProgramClicked();
    void onAddStudentToProgramClicked();
    void onRemoveStudentFromProgramClicked();
    void onAddProgramClicked();
    void onAddTeacherClicked();
    void onRemoveTeacherClicked();
    void onRemoveTeacherFromProgramClicked2();
};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStringListModel>
#include <QString>
#include <QMessageBox>
#include "itemdetailsdialog.h"
#include "confirmremovedialog.h"
#include "addprogramdialog.h"
#include "additemtoprogramdialog.h"
#include "addteacherdialog.h"
#include "../model/teacherprogramlistmodel.h"
#include "../services/programteacherassociationservice.h"
#include "../services/programstudentassociationservice.h"

MainWindow::MainWindow(School* school,
                       ProgramService &programService,
                       TeacherService &teacherService,
                       ProgramTeacherAssociationService &programTeacherService,
                       ProgramStudentAssociationService &programStudentService,
                       QWidget* parent)
    : QMainWindow(parent)
    , school_(school)
    , programService_(programService)
    , teacherService_(teacherService)
    , programTeacherService_(programTeacherService)
    , programStudentService_(programStudentService)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    ui_->titleLabel->setText(school_->name());

    programModel_ = new ProgramListModel(this);
    programTeacherModel_ = new ProgramTeacherListModel(this);
    programStudentModel_ = new ProgramStudentListModel(this);
    teacherModel_ = new TeachersListModel(this);
    teacherProgramModel_ = new TeacherProgramListModel(this);

    ui_->koulutusohjelmatListView->setModel(programModel_);
    ui_->koulutusOhjelmanOpettajatListView->setModel(programTeacherModel_);
    ui_->koulutusOhjelmanOppilaatListView->setModel(programStudentModel_);
    ui_->opettajatListView_2->setModel(teacherModel_);
    ui_->opettajanKoulutusOhjelmatListView->setModel(teacherProgramModel_);

    connect(ui_->koulutusohjelmatListView->selectionModel(),
            &QItemSelectionModel::currentChanged,
            this,
            [this](const QModelIndex& current, const QModelIndex&)
            {
                Program program = programModel_->programAt(current.row());
                ui_->lisatiedotLabel->setText(program.name());

                programTeacherModel_->setTeachers(
                    programTeacherService_.fetchAssigned(program.id().toInt()));
                programStudentModel_->setStudents(
                    programStudentService_.fetchAssigned(program.id().toInt()));
            });

    connect(ui_->koulutusohjelmatListView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            [this](const QItemSelection& selection, const QItemSelection&)
            {
                ui_->poistaKoulutusohjelmaButton->setEnabled(!selection.isEmpty());
                ui_->lisaaOpettajaKoulutusOhjelmaanButton->setEnabled(!selection.isEmpty());
                ui_->lisaaOppilasKoulutusOhjelmaanButton->setEnabled(!selection.isEmpty());
            });

    connect(ui_->koulutusOhjelmanOpettajatListView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            [this](const QItemSelection& selection, const QItemSelection& deselected)
            {
                ui_->poistaOpettajaKoulutusOhjelmastaButton->setEnabled(!selection.isEmpty());
            });
    connect(ui_->koulutusOhjelmanOppilaatListView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            [this](const QItemSelection& selection, const QItemSelection& deselected)
            {
                ui_->poistaOppilasKoulutusOhjelmastaButton->setEnabled(!selection.isEmpty());
            });

    connect(programTeacherModel_,
            &QAbstractListModel::modelReset,
            this,
            [this]()
            {
                ui_->poistaOpettajaKoulutusOhjelmastaButton->setEnabled(false);
            });
    connect(programStudentModel_,
            &QAbstractListModel::modelReset,
            this,
            [this]()
            {
                ui_->poistaOppilasKoulutusOhjelmastaButton->setEnabled(false);
            });

    connect(ui_->koulutusOhjelmanOpettajatListView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            [this](const QItemSelection &selection, const QItemSelection deselected)
            {
                ui_->poistaOpettajaKoulutusOhjelmastaButton->setEnabled(!selection.isEmpty());
            });

    connect(ui_->koulutusohjelmatListView, &QListView::doubleClicked, this, &MainWindow::onItemDoubleClicked);

    connect(programModel_, &QAbstractItemModel::rowsInserted, this, &MainWindow::updateProgramCount);
    connect(programModel_, &QAbstractItemModel::rowsRemoved, this, &MainWindow::updateProgramCount);
    connect(programModel_,
            &QAbstractItemModel::modelReset,
            this,
            [this]()
            {
                programTeacherModel_->setTeachers(std::vector<AssociationItem>());
                programStudentModel_->setStudents(std::vector<AssociationItem>());
                ui_->poistaKoulutusohjelmaButton->setEnabled(false);
                updateProgramCount();
            });
    updateProgramCount();

    connect(teacherModel_, &QAbstractItemModel::rowsInserted, this, &MainWindow::updateOpettajatCount);
    connect(teacherModel_, &QAbstractItemModel::rowsRemoved, this, &MainWindow::updateOpettajatCount);
    connect(teacherModel_,
            &QAbstractItemModel::modelReset,
            this,
            [this]()
            {
                ui_->poistaOpettaja->setEnabled(false);
                updateOpettajatCount();
            });

    connect(ui_->opettajatListView_2->selectionModel(),
            &QItemSelectionModel::currentChanged,
            this,
            [this](const QModelIndex& current, const QModelIndex&)
            {
                Teacher teacher = teacherModel_->teacherAt(current.row());
                teacherProgramModel_->setPrograms(
                    programTeacherService_.fetchPrograms(teacher.id().toInt()));
            });
    connect(ui_->opettajatListView_2->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            [this](const QItemSelection& selected, const QItemSelection& deselected)
            {
                ui_->poistaOpettaja->setEnabled(!selected.isEmpty());
            });
    updateOpettajatCount();

    connect(teacherProgramModel_,
            &QAbstractListModel::modelReset,
            this,
            [this](){
                ui_->poistaOpettajaKoulutusOhjelmastaButton_2->setEnabled(false);
            });
    connect(ui_->opettajanKoulutusOhjelmatListView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            [this](const QItemSelection& selected, const QItemSelection& deselected){
                ui_->poistaOpettajaKoulutusOhjelmastaButton_2->setEnabled(!selected.isEmpty());
            });


    connect(ui_->lisaaOpettajaKoulutusOhjelmaanButton, &QPushButton::clicked, this, &MainWindow::onAddTeacherToProgramClicked);
    connect(ui_->poistaOpettajaKoulutusOhjelmastaButton, &QPushButton::clicked, this, &MainWindow::onRemoveTeacherFromProgramClicked);

    connect(ui_->lisaaOppilasKoulutusOhjelmaanButton, &QPushButton::clicked, this, &MainWindow::onAddStudentToProgramClicked);
    connect(ui_->poistaOppilasKoulutusOhjelmastaButton, &QPushButton::clicked, this, &MainWindow::onRemoveStudentFromProgramClicked);

    connect(ui_->lisaaKoulutusohjelmaButton, &QPushButton::clicked, this, &MainWindow::onAddProgramClicked);
    connect(ui_->poistaKoulutusohjelmaButton, &QPushButton::clicked, this, &MainWindow::onRemoveProgramClicked);

    connect(ui_->lisaaOpettaja, &QPushButton::clicked, this, &MainWindow::onAddTeacherClicked);
    connect(ui_->poistaOpettaja, &QPushButton::clicked, this, &MainWindow::onRemoveTeacherClicked);

    connect(ui_->poistaOpettajaKoulutusOhjelmastaButton_2, &QPushButton::clicked, this, &MainWindow::onRemoveTeacherFromProgramClicked2);


    programModel_->setPrograms(programService_.fetchPrograms());
    teacherModel_->setTeachers(teacherService_.fetchTeachers());
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::onRemoveTeacherFromProgramClicked2()
{
    QItemSelectionModel* selectionModel = ui_->opettajanKoulutusOhjelmatListView->selectionModel();
    QModelIndex current = ui_->opettajanKoulutusOhjelmatListView->currentIndex();
    if (!current.isValid())
        return;
    Program program = teacherProgramModel_->programAt(current.row());
    if (program.id() == "")
        return;
    ConfirmRemoveDialog dialog(this);

    dialog.setObjectName(program.name());
    if (dialog.exec() != QDialog::Accepted)
        return;

    QModelIndex currentTeacher = ui_->opettajatListView_2->currentIndex();
    if (!current.isValid())
        return;
    Teacher teacher = teacherModel_->teacherAt(currentTeacher.row());

    programTeacherService_.unlink(program.id().toInt(), teacher.id().toInt());
    selectionModel->clearSelection();
    teacherProgramModel_->setPrograms(
        programTeacherService_.fetchPrograms(teacher.id().toInt()));

    programTeacherModel_->setTeachers(programTeacherService_.fetchAssigned(program.id().toInt()));
}

void MainWindow::onAddTeacherClicked()
{
    AddTeacherDialog dialog(this);
    if (dialog.exec() != QDialog::Accepted)
        return;

    teacherService_.addTeacher(dialog.teacher());
    teacherModel_->setTeachers(teacherService_.fetchTeachers());
}

void MainWindow::onRemoveTeacherClicked()
{
    QModelIndex current = ui_->opettajatListView_2->currentIndex();
    if (!current.isValid())
        return;

    Teacher teacher = teacherModel_->teacherAt(current.row());
    ConfirmRemoveDialog dialog(this);
    dialog.setObjectName(teacher.fullName());
    if (dialog.exec() != QDialog::Accepted)
        return;

    teacherService_.removeTeacher(teacher.id().toInt());
    teacherModel_->setTeachers(teacherService_.fetchTeachers());
}

void MainWindow::onAddProgramClicked()
{
    AddProgramDialog dialog(this);
    if (dialog.exec() != QDialog::Accepted)
        return;

    programService_.addProgram(school_->id().toInt(), dialog.program());
    programModel_->setPrograms(programService_.fetchPrograms());
}

void MainWindow::onRemoveProgramClicked()
{
    QItemSelectionModel* selectionModel = ui_->koulutusohjelmatListView->selectionModel();
    QModelIndex current = ui_->koulutusohjelmatListView->currentIndex();
    if (!current.isValid())
        return;

    Program program = programModel_->programAt(current.row());
    ConfirmRemoveDialog dialog(this);
    dialog.setObjectName(program.name());
    if (dialog.exec() != QDialog::Accepted)
        return;

    programService_.removeProgram(program.id().toInt());
    selectionModel->clearSelection();
    programModel_->setPrograms(programService_.fetchPrograms());
    ui_->lisatiedotLabel->setText(QString());
}

void MainWindow::onAddStudentToProgramClicked()
{
    QModelIndex currentKoulutusOhjelma = ui_->koulutusohjelmatListView->currentIndex();
    if (!currentKoulutusOhjelma.isValid())
        return;
    Program program = programModel_->programAt(currentKoulutusOhjelma.row());

    AddItemToProgramDialog dialog(
        program,
        programStudentService_,
        this);
    if (dialog.exec() != QDialog::Accepted)
        return;
    programStudentModel_->setStudents(
        programStudentService_.fetchAssigned(program.id().toInt()));
}

void MainWindow::onRemoveStudentFromProgramClicked()
{
    QItemSelectionModel* selectionModel = ui_->koulutusOhjelmanOpettajatListView->selectionModel();
    QModelIndex current = ui_->koulutusOhjelmanOppilaatListView->currentIndex();
    if (!current.isValid())
        return;
    AssociationItem student = programStudentModel_->studentAt(current.row());
    if (student.id == 0)
        return;
    ConfirmRemoveDialog dialog(this);

    dialog.setObjectName(student.displayName);
    if (dialog.exec() != QDialog::Accepted)
        return;

    QModelIndex currentProgram = ui_->koulutusohjelmatListView->currentIndex();
    if (!current.isValid())
        return;
    Program program = programModel_->programAt(currentProgram.row());

    programStudentService_.unlink(program.id().toInt(), student.id);
    selectionModel->clearSelection();
    programStudentModel_->setStudents(
        programStudentService_.fetchAssigned(program.id().toInt()));
}

void MainWindow::onAddTeacherToProgramClicked()
{
    QModelIndex currentProgram = ui_->koulutusohjelmatListView->currentIndex();
    if (!currentProgram.isValid())
        return;
    Program program = programModel_->programAt(currentProgram.row());

    AddItemToProgramDialog dialog(
        program,
        programTeacherService_,
        this);
    if (dialog.exec() != QDialog::Accepted)
        return;

    programTeacherModel_->setTeachers(programTeacherService_.fetchAssigned(program.id().toInt()));
}

void MainWindow::onRemoveTeacherFromProgramClicked()
{
    QItemSelectionModel* selectionModel = ui_->koulutusOhjelmanOpettajatListView->selectionModel();
    QModelIndex current = ui_->koulutusOhjelmanOpettajatListView->currentIndex();
    if (!current.isValid())
        return;
    AssociationItem teacher = programTeacherModel_->teacherAt(current.row());
    if (teacher.id == 0)
        return;
    ConfirmRemoveDialog dialog(this);

    dialog.setObjectName(teacher.displayName);
    if (dialog.exec() != QDialog::Accepted)
        return;

    QModelIndex currentProgram = ui_->koulutusohjelmatListView->currentIndex();
    if (!current.isValid())
        return;
    Program program = programModel_->programAt(currentProgram.row());

    programTeacherService_.unlink(program.id().toInt(), teacher.id);
    selectionModel->clearSelection();
    programTeacherModel_->setTeachers(programTeacherService_.fetchAssigned(program.id().toInt()));
}

void MainWindow::onItemDoubleClicked(const QModelIndex& index)
{
    if (!index.isValid())
        return;

    QString itemText = index.data(Qt::DisplayRole).toString();
    ItemDetailsDialog dialog(itemText, this);
    dialog.exec();
}

void MainWindow::onItemClicked(const QModelIndex& index)
{
    if (!index.isValid())
        return;

    Program program = programModel_->programAt(index.row());
    ui_->lisatiedotLabel->setText(program.name());
}

void MainWindow::updateProgramCount()
{
    int count = programModel_->rowCount();
    ui_->koulutusohjelmatCountLabel->setText(QString("Koulutusohjelmien määrä: %1").arg(count));
}

void MainWindow::updateOpettajatCount()
{
    int count = teacherModel_->rowCount();
    ui_->opettajienMaaraLabel->setText(QString("Opettajien määrä: %1").arg(count));
}

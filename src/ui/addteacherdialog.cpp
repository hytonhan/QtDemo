#include <QMessageBox>
#include "addteacherdialog.h"
#include "ui_addteacherdialog.h"

AddTeacherDialog::AddTeacherDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddTeacherDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Lisää opettaja"));
}

AddTeacherDialog::~AddTeacherDialog()
{
    delete ui;
}


void AddTeacherDialog::onAddClicked()
{
    QString firstName = ui->firstNameLineEdit->text().trimmed();
    if (firstName.isEmpty())
    {
        QMessageBox::warning(
            this,
            tr("Virheellinen syöte"),
            tr("Etunimi ei voi olla tyhjä.")
            );
        return;
    }
    QString lastName = ui->lastNameLineEdit->text().trimmed();
    if (lastName.isEmpty())
    {
        QMessageBox::warning(
            this,
            tr("Virheellinen syöte"),
            tr("Sukunimi ei voi olla tyhjä.")
            );
        return;
    }
    QString field = ui->fieldLineEdit->text().trimmed();
    if (field.isEmpty())
    {
        QMessageBox::warning(
            this,
            tr("Virheellinen syöte"),
            tr("Ala ei voi olla tyhjä.")
            );
        return;
    }
    QString salary = ui->salaryLineEdit->text().trimmed();
    if (salary.isEmpty())
    {
        QMessageBox::warning(
            this,
            tr("Virheellinen syöte"),
            tr("Palkka ei voi olla tyhjä.")
            );
        return;
    }
    QString address = ui->addressLineEdit->text().trimmed();
    QString phone = ui->phoneLineEdit->text().trimmed();

    accept();
}

Teacher AddTeacherDialog::teacher() const
{
    return Teacher(
        ui->firstNameLineEdit->text().trimmed(),
        ui->lastNameLineEdit->text().trimmed(),
        ui->addressLineEdit->text().trimmed(),
        ui->phoneLineEdit->text().trimmed(),
        QString(),
        ui->salaryLineEdit->text().trimmed().toFloat(),
        ui->fieldLineEdit->text().trimmed());
}

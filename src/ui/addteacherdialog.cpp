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
    QString firstName = ui->etunimiLineEdit->text().trimmed();
    if (firstName.isEmpty())
    {
        QMessageBox::warning(
            this,
            tr("Virheellinen syöte"),
            tr("Etunimi ei voi olla tyhjä.")
            );
        return;
    }
    QString lastName = ui->sukunimiLineEdit->text().trimmed();
    if (lastName.isEmpty())
    {
        QMessageBox::warning(
            this,
            tr("Virheellinen syöte"),
            tr("Sukunimi ei voi olla tyhjä.")
            );
        return;
    }
    QString field = ui->alaLineEdit->text().trimmed();
    if (field.isEmpty())
    {
        QMessageBox::warning(
            this,
            tr("Virheellinen syöte"),
            tr("Ala ei voi olla tyhjä.")
            );
        return;
    }
    QString salary = ui->palkkaLineEdit->text().trimmed();
    if (salary.isEmpty())
    {
        QMessageBox::warning(
            this,
            tr("Virheellinen syöte"),
            tr("Palkka ei voi olla tyhjä.")
            );
        return;
    }
    QString address = ui->osoiteLineEdit->text().trimmed();
    QString phone = ui->puhelinLineEdit->text().trimmed();

    accept();
}

Teacher AddTeacherDialog::teacher() const
{
    return Teacher(
        ui->etunimiLineEdit->text().trimmed(),
        ui->sukunimiLineEdit->text().trimmed(),
        ui->osoiteLineEdit->text().trimmed(),
        ui->puhelinLineEdit->text().trimmed(),
        QString(),
        ui->palkkaLineEdit->text().trimmed().toFloat(),
        ui->alaLineEdit->text().trimmed());
}

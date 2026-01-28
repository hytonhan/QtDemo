#include <QMessageBox>
#include "addopiskelijadialog.h".h"
#include "ui_add

AddTeacherDialog::AddTeacherDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddOpiskelijaDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Lisää teacher"));
}

AddTeacherDialog::~AddTeacherDialog()
{
    delete ui;
}


void AddTeacherDialog::onAddClicked()
{
    QString etunimi = ui->etunimiLineEdit->text().trimmed();
    if (etunimi.isEmpty())
    {
        QMessageBox::warning(
            this,
            tr("Virheellinen syöte"),
            tr("Etunimi ei voi olla tyhjä.")
            );
        return;
    }
    QString sukunimi = ui->sukunimiLineEdit->text().trimmed();
    if (sukunimi.isEmpty())
    {
        QMessageBox::warning(
            this,
            tr("Virheellinen syöte"),
            tr("Sukunimi ei voi olla tyhjä.")
            );
        return;
    }
    QString ala = ui->alaLineEdit->text().trimmed();
    if (ala.isEmpty())
    {
        QMessageBox::warning(
            this,
            tr("Virheellinen syöte"),
            tr("Ala ei voi olla tyhjä.")
            );
        return;
    }
    QString palkka = ui->palkkaLineEdit->text().trimmed();
    if (palkka.isEmpty())
    {
        QMessageBox::warning(
            this,
            tr("Virheellinen syöte"),
            tr("Palkka ei voi olla tyhjä.")
            );
        return;
    }
    QString osoite = ui->osoiteLineEdit->text().trimmed();
    QString puhelin = ui->puhelinLineEdit->text().trimmed();

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

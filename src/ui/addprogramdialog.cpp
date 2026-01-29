#include <QMessageBox>
#include "addprogramdialog.h"
#include "ui_addprogramdialog.h"

AddProgramDialog::AddProgramDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddProgramDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Lisää koulutusohjelma"));
}

AddProgramDialog::~AddProgramDialog()
{
    delete ui;
}


void AddProgramDialog::onAddClicked()
{
    QString name = ui->nimiLineEdit->text().trimmed();
    if (name.isEmpty())
    {
        QMessageBox::warning(
            this,
            tr("Invalid input"),
            tr("Program name cannot be empty.")
            );
        return;
    }

    accept();
}

Program AddProgramDialog::program() const
{
    return Program(
        "",
        ui->nimiLineEdit->text().trimmed()
    );
}


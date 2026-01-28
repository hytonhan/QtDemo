#include "confirmremovedialog.h"
#include "ui/ui_confirmremovedialog.h"

ConfirmRemoveDialog::ConfirmRemoveDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConfirmRemoveDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

ConfirmRemoveDialog::~ConfirmRemoveDialog()
{
    delete ui;
}

void ConfirmRemoveDialog::setObjectName(const QString& name)
{
    ui->label->setText(
        tr("Haluatko varmasti poistaa rivin \"%1\"?\nTätä toimintoa ei voi peruuttaa.")
            .arg(name)
        );
}

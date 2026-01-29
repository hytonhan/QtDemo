#include "itemdetailsdialog.h"
#include "ui_itemdetailsdialog.h"

ItemDetailsDialog::ItemDetailsDialog(const QString& itemName, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ItemDetailsDialog)
{
    ui->setupUi(this);

    ui->label->setText("Details for: " + itemName);
}

ItemDetailsDialog::~ItemDetailsDialog()
{
    delete ui;
}

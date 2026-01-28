#ifndef ITEMDETAILSDIALOG_H
#define ITEMDETAILSDIALOG_H

#include <QDialog>

namespace Ui {
class ItemDetailsDialog;
}

class ItemDetailsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ItemDetailsDialog(const QString& itemName, QWidget *parent = nullptr);
    ~ItemDetailsDialog();

private:
    Ui::ItemDetailsDialog *ui;
};

#endif // ITEMDETAILSDIALOG_H

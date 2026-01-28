#ifndef CONFIRMREMOVEDIALOG_H
#define CONFIRMREMOVEDIALOG_H

#include <QDialog>

namespace Ui {
class ConfirmRemoveDialog;
}

class ConfirmRemoveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmRemoveDialog(QWidget *parent = nullptr);
    ~ConfirmRemoveDialog();

    void setObjectName(const QString& name);

private:
    Ui::ConfirmRemoveDialog *ui;
};

#endif // CONFIRMREMOVEDIALOG_H

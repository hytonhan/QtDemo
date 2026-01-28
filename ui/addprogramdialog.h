#ifndef ADDPROGRAMDIALOG_H
#define ADDPROGRAMDIALOG_H

#include <QDialog>
#include "../domain/program.h"

namespace Ui {
class AddProgramDialog;
}

class AddProgramDialog : public QDialog
{
    Q_OBJECT

public:
    AddProgramDialog(QWidget *parent = nullptr);
    ~AddProgramDialog();

    Program program() const;

private slots:
    void onAddClicked();

private:
    Ui::AddProgramDialog *ui;
};

#endif // ADDPROGRAMDIALOG_H

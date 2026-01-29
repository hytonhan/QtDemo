#ifndef ADDTEACHERDIALOG_H
#define ADDTEACHERDIALOG_H

#include <QDialog>
#include "../domain/teacher.h"

namespace Ui {
class AddTeacherDialog;
}

class AddTeacherDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTeacherDialog(QWidget *parent = nullptr);
    ~AddTeacherDialog();

    Teacher teacher() const;

private slots:
    void onAddClicked();

private:
    Ui::AddTeacherDialog *ui;
};

#endif // ADDTEACHERDIALOG_H

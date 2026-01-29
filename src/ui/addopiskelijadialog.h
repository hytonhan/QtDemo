#ifndef ADDOPISKELIJADIALOG_H
#define ADDOPISKELIJADIALOG_H

#include <QDialog>
#include "../domain/student.h"

namespace Ui {
class AddOpiskelijaDialog;
}

class AddOpiskelijaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddOpiskelijaDialog(QWidget *parent = nullptr);
    ~AddOpiskelijaDialog();

    Student student() const;

private slots:
    void onAddClicked();

private:
    Ui::AddOpiskelijaDialog *ui;
};

#endif // ADDOPISKELIJADIALOG_H

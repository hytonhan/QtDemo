#ifndef ADDITEMTOPROGRAMDIALOG_H
#define ADDITEMTOPROGRAMDIALOG_H

#include <QDialog>
#include <QVector>
#include "../model/programassociationitemlistmodel.h"
#include "../domain/program.h"
#include "../services/programassociationservice.h"

namespace Ui {
class AddItemToProgramDialog;
}

class AddItemToProgramDialog : public QDialog
{
    Q_OBJECT

public:
    AddItemToProgramDialog(
        const Program& program,
        ProgramAssociationService& associationService,
        QWidget *parent = nullptr
    );
    ~AddItemToProgramDialog();

private slots:
    void onAddButtonClicked();
    void onAddClicked();
    void onRemoveClicked();
private:
    void refresh();

    std::vector<int> originalIds_;
    Ui::AddItemToProgramDialog *ui_;
    const Program& program_;
    ProgramAssociationItemListModel* availableModel_;
    ProgramAssociationItemListModel* assignedModel_;
    ProgramAssociationService& associationService_;
};

#endif // ADDITEMTOPROGRAMDIALOG_H

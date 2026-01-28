#include "additemtoprogramdialog.h"
#include "ui_additemtoprogramdialog.h"

AddItemToProgramDialog::AddItemToProgramDialog(
    const Program& program,
    ProgramAssociationService& associationService,
    QWidget *parent)
    : QDialog(parent)
    , program_(program)
    , associationService_(associationService)
    , ui_(new Ui::AddItemToProgramDialog)
{
    ui_->setupUi(this);
    setWindowTitle(tr("Lisää jotakin koulutusohjelmaan"));

    availableModel_ = new ProgramAssociationItemListModel(this);
    assignedModel_ = new ProgramAssociationItemListModel(this);

    ui_->lisattavatListView->setModel(availableModel_);
    ui_->lisatytListView->setModel(assignedModel_);

    auto available = associationService_.fetchAvailable(program_.id().toInt());
    auto assigned = associationService_.fetchAssigned(program_.id().toInt());

    availableModel_->setItems(available);
    assignedModel_->setItems(assigned);

    std::vector<int> originals;
    for(auto& a: assigned) {
        originals.push_back(a.id);
    }
    originalIds_ = originals;
}

AddItemToProgramDialog::~AddItemToProgramDialog()
{
    delete ui_;
}

void AddItemToProgramDialog::onAddButtonClicked()
{
    for (int entityId : assignedModel_->ids()) {
        if (std::find(originalIds_.begin(), originalIds_.end(), entityId) == originalIds_.end()) {
            associationService_.link(program_.id().toInt(), entityId);
        }
    }

    const auto currentIds = assignedModel_->ids();
    for (int entityId : std::as_const(originalIds_)) {
        if (std::find(currentIds.begin(), currentIds.end(), entityId) == currentIds.end()) {
            associationService_.unlink(program_.id().toInt(), entityId);
        }
    }

    accept();
}

void AddItemToProgramDialog::onAddClicked()
{
    QModelIndex index = ui_->lisattavatListView->currentIndex();
    if (!index.isValid())
        return;

    assignedModel_->add(availableModel_->takeAt(index.row()));
}

void AddItemToProgramDialog::onRemoveClicked()
{
    QModelIndex index = ui_->lisatytListView->currentIndex();
    if (!index.isValid())
        return;

    availableModel_->add(assignedModel_->takeAt(index.row()));
}


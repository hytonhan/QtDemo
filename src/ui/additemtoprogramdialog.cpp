#include "additemtoprogramdialog.h"
#include "ui_additemtoprogramdialog.h"
#include <QMessageBox>

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

    ui_->availableListView ->setModel(availableModel_);
    ui_->assignedListView->setModel(assignedModel_);

    auto available = associationService_.fetchAvailable(program_.id().toInt());
    if (std::holds_alternative<QString>(available)) {
        qCritical() << std::get<QString>(available);
        QMessageBox::critical(nullptr,
                              QObject::tr("Loading error"),
                              QObject::tr("The application could not load required data."));
    }

    auto assigned = associationService_.fetchAssigned(program_.id().toInt());
    if (std::holds_alternative<QString>(assigned)) {
        qCritical() << std::get<QString>(assigned);
        QMessageBox::critical(nullptr,
                              QObject::tr("Loading error"),
                              QObject::tr("The application could not load required data."));
    }

    availableModel_->setItems(std::get<std::vector<AssociationItem>>(available));
    assignedModel_->setItems(std::get<std::vector<AssociationItem>>(assigned));

    std::vector<int> originals;
    for(auto& a: std::get<std::vector<AssociationItem>>(assigned)) {
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
    QModelIndex index = ui_->availableListView->currentIndex();
    if (!index.isValid())
        return;

    assignedModel_->add(availableModel_->takeAt(index.row()));
}

void AddItemToProgramDialog::onRemoveClicked()
{
    QModelIndex index = ui_->assignedListView->currentIndex();
    if (!index.isValid())
        return;

    availableModel_->add(assignedModel_->takeAt(index.row()));
}


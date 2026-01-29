#include "programassociationitemlistmodel.h"

ProgramAssociationItemListModel::ProgramAssociationItemListModel(QObject *parent)
    : QAbstractListModel{parent}
{}

int ProgramAssociationItemListModel::rowCount(const QModelIndex&) const {
    return items_.size();
}

QVariant ProgramAssociationItemListModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return {};
    return items_[index.row()].displayName;
}

void ProgramAssociationItemListModel::setItems(std::vector<AssociationItem> items) {
    beginResetModel();
    items_ = std::move(items);
    endResetModel();
}

AssociationItem ProgramAssociationItemListModel::takeAt(int row) {
    beginRemoveRows({}, row, row);
    auto item = std::move(items_[row]);
    items_.erase(items_.begin() + row);
    endRemoveRows();
    return item;
}

void ProgramAssociationItemListModel::add(AssociationItem item) {
    beginInsertRows({}, items_.size(), items_.size());
    items_.push_back(std::move(item));
    endInsertRows();
}

std::vector<int> ProgramAssociationItemListModel::ids() const {
    std::vector<int> result;
    for (const auto& i : items_)
        result.push_back(i.id);
    return result;
}

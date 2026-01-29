#include "teacherlistmodel.h"

TeachersListModel::TeachersListModel(QObject* parent)
    : QAbstractListModel(parent)
{}

int TeachersListModel::rowCount(const QModelIndex&) const
{
    return teachers_.size();
}

QVariant TeachersListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() < 0 || index.row() >= static_cast<int>(teachers_.size()))
        return QVariant();
    if (role != Qt::DisplayRole)
        return QVariant();

    return teachers_.at(index.row()).fullName();
}

void TeachersListModel::setTeachers(std::vector<Teacher> teachers)
{
    beginResetModel();
    teachers_ = std::move(teachers);
    endResetModel();
}

const Teacher& TeachersListModel::teacherAt(int row) const
{
    return teachers_[row];
}





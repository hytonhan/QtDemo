#include "programteacherlistmodel.h"

ProgramTeacherListModel::ProgramTeacherListModel(QObject* parent)
    : QAbstractListModel(parent)
{}

int ProgramTeacherListModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return static_cast<int>(teachers_.size());
}

QVariant ProgramTeacherListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return {};

    if (index.row() < 0 || index.row() >= static_cast<int>(teachers_.size()))
        return {};

    if (role == Qt::DisplayRole)
        return teachers_[index.row()].displayName;

    return {};
}

const AssociationItem& ProgramTeacherListModel::teacherAt(int row) const
{
    return teachers_[row];
}

void ProgramTeacherListModel::setTeachers(std::vector<AssociationItem> teachers)
{
    beginResetModel();
    teachers_ = std::move(teachers);
    endResetModel();
}


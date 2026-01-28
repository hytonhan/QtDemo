#include "programstudentlistmodel.h"

ProgramStudentListModel::ProgramStudentListModel(QObject* parent)
    : QAbstractListModel(parent)
{}

int ProgramStudentListModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return static_cast<int>(students_.size());
}

QVariant ProgramStudentListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return {};

    if (index.row() < 0 || index.row() >= static_cast<int>(students_.size()))
        return {};

    if (role == Qt::DisplayRole)
        return students_[index.row()].displayName;

    return {};
}

const AssociationItem &ProgramStudentListModel::studentAt(int row) const
{
    return students_[row];
}

void ProgramStudentListModel::setStudents(std::vector<AssociationItem> students)
{
    beginResetModel();
    students_ = std::move(students);
    endResetModel();
}

#include "programlistmodel.h"

ProgramListModel::ProgramListModel(QObject* parent)
    : QAbstractListModel(parent)
{}

int ProgramListModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return static_cast<int>(programs_.size());
}

QVariant ProgramListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() < 0 || index.row() >= static_cast<int>(programs_.size()))
        return QVariant();
    if (role != Qt::DisplayRole)
        return QVariant();

    return programs_[index.row()].name();
}

const Program& ProgramListModel::programAt(int row) const
{
    return programs_[row];
}

void ProgramListModel::setPrograms(std::vector<Program> programs)
{
    beginResetModel();
    programs_ = std::move(programs);
    endResetModel();
}


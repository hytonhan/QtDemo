#include "teacherprogramlistmodel.h"

TeacherProgramListModel::TeacherProgramListModel(QObject* parent)
    : QAbstractListModel(parent)
{}

int TeacherProgramListModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return static_cast<int>(programs_.size());
}

QVariant TeacherProgramListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return {};

    if (index.row() < 0 || index.row() >= static_cast<int>(programs_.size()))
        return {};

    if (role == Qt::DisplayRole)
        return programs_[index.row()].name();

    return {};
}

const Program& TeacherProgramListModel::programAt(int row) const
{
    return programs_[row];
}

void TeacherProgramListModel::setPrograms(std::vector<Program> programs)
{
    beginResetModel();
    programs_ = std::move(programs);
    endResetModel();
}

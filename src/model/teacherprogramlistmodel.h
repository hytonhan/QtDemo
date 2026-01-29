#ifndef TEACHERPROGRAMLISTMODEL_H
#define TEACHERPROGRAMLISTMODEL_H

#pragma once

#include <QAbstractListModel>
#include "../domain/program.h"

class TeacherProgramListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TeacherProgramListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int rol) const override;

    const Program& programAt(int row) const;
    void setPrograms(std::vector<Program> programs);
private:
    std::vector<Program> programs_;
};

#endif // TEACHERPROGRAMLISTMODEL_H

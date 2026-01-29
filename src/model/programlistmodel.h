#ifndef PROGRAMLISTMODEL_H
#define PROGRAMLISTMODEL_H

#pragma once

#include <QAbstractListModel>
#include "../domain/program.h"

class ProgramListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ProgramListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int rol) const override;

    const Program& programAt(int row) const;
    void setPrograms(std::vector<Program> programs);
private:
    std::vector<Program> programs_;
};

#endif // PROGRAMLISTMODEL_H

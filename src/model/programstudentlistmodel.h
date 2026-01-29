#ifndef PROGRAMSTUDENTLISTMODEL_H
#define PROGRAMSTUDENTLISTMODEL_H

#pragma once

#include <QAbstractListModel>
#include "../services/programassociationservice.h"

class ProgramStudentListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ProgramStudentListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int rol) const override;

    void setStudents(std::vector<AssociationItem> students);
    const AssociationItem& studentAt(int row) const;
private:
    std::vector<AssociationItem> students_;
};

#endif // PROGRAMSTUDENTLISTMODEL_H

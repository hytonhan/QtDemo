#ifndef PROGRAMTEACHERLISTMODEL_H
#define PROGRAMTEACHERLISTMODEL_H

#pragma once

#include <QAbstractListModel>
#include "../services/programassociationservice.h"

class ProgramTeacherListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ProgramTeacherListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int rol) const override;

    void setTeachers(std::vector<AssociationItem> teachers);
    const AssociationItem& teacherAt(int row) const;
private:
    std::vector<AssociationItem> teachers_;
};

#endif // PROGRAMTEACHERLISTMODEL_H

#ifndef TEACHERLISTMODEL_H
#define TEACHERLISTMODEL_H

#pragma once

#include <QAbstractListModel>
#include "../domain/teacher.h"

class TeachersListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TeachersListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;

    const Teacher& teacherAt(int row) const;
    void setTeachers(std::vector<Teacher> teachers);

private:
    std::vector<Teacher> teachers_;
};

#endif // TEACHERLISTMODEL_H

#ifndef PROGRAMASSOCIATIONITEMLISTMODEL_H
#define PROGRAMASSOCIATIONITEMLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include "../services/programassociationservice.h"

class ProgramAssociationItemListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ProgramAssociationItemListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex&) const override;
    QVariant data(const QModelIndex& index, int role) const override;

    void setItems(std::vector<AssociationItem> items);
    AssociationItem takeAt(int row);
    void add(AssociationItem item);

    std::vector<int> ids() const;

private:
    std::vector<AssociationItem> items_;
};

#endif // PROGRAMASSOCIATIONITEMLISTMODEL_H

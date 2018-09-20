#ifndef FREQDIALOGMODEL_H
#define FREQDIALOGMODEL_H

#include <QAbstractTableModel>
#include "types.h"

class FreqDialogModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    FreqDialogModel(struct Params *p_params, struct FreqSet *p_freqSet, QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    struct Params *params;
    struct FreqSet *freqSet;
};

#endif // FREQDIALOGMODEL_H

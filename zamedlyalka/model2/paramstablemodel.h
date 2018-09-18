#ifndef NORMPARAMSMODEL_H
#define NORMPARAMSMODEL_H

#include <QAbstractTableModel>
#include "types.h"

class ParamsTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ParamsTableModel(struct Params *p_params, QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const{return 1;}
    int columnCount(const QModelIndex &parent) const{return params->COUNT;}
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
signals:
    void normParamsChanged();

private:
    struct Params *params;
};

#endif // NORMPARAMSMODEL_H

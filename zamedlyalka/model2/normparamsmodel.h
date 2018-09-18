#ifndef NORMPARAMSMODEL_H
#define NORMPARAMSMODEL_H

#include <QAbstractTableModel>
#include "types.h"

class NormParamsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    NormParamsModel(struct NormParams *normParams, QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const{return 3;}
    int columnCount(const QModelIndex &parent) const{return 3;}
    QVariant data(const QModelIndex &index, int role) const;
signals:
    void normParamsChanged();

private:
    struct NormParams *normParams;
};

#endif // NORMPARAMSMODEL_H

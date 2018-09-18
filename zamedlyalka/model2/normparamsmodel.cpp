#include "normparamsmodel.h"

NormParamsModel::NormParamsModel(struct NormParams *normParams, QObject *parent)
    :QAbstractTableModel(parent)
{

}

QVariant NormParamsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() == 0)
    {
        if (index.column() == 0)
        {
            //
        }
        else if (index.column() == 1)
        {
            //
        }
        else if (index.column() == 2)
        {
            //
        }
    }
    else if (index.row() == 1)
    {
        if (index.column() == 0)
        {
            //
        }
        else if (index.column() == 1)
        {
            //
        }
        else if (index.column() == 2)
        {
            //
        }
    }
    return QVariant();
}

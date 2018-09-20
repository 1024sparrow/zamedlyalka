#include "freqdialogmodel.h"

FreqDialogModel::FreqDialogModel(struct Params *p_params, struct FreqSet *p_freqSet, QObject *parent)
    :QAbstractTableModel(parent)
{

}

int FreqDialogModel::rowCount(const QModelIndex &parent) const
{
    return 2;
}

int FreqDialogModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant FreqDialogModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            if (section == 0)
                return "1/4";
            else if (section == 1)
                return "2/4";
            else if (section == 2)
                return "3/4";
            else if (section == 3)
                return "4/4";
        }
        else if (orientation == Qt::Vertical)
        {
            //
        }
    }
    return QVariant();
}

QVariant FreqDialogModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

bool FreqDialogModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return false;
}

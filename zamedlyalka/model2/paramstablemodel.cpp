#include "paramstablemodel.h"
#include <QColor>

ParamsTableModel::ParamsTableModel(Params *p_params, QObject *parent)
    :QAbstractTableModel(parent), params(p_params)
{

}

QVariant ParamsTableModel::data(const QModelIndex &index, int role) const
{
    int col = index.column();
    if (role == Qt::DisplayRole)
    {
        if (col == 0)
            return params->quality;
        else if (col == 1)
            return params->discretFreq;
        else if (col == 2)
            return params->tickCountPerKick;
        else if (col == 3)
            return params->freqCount;
    }
    return QVariant();
}

QVariant ParamsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical)
        return QVariant();
    if (role == Qt::ToolTipRole)
    {
        if (section == 0)
            return "Добротность";
        else if (section == 1)
            return "Частота дискретизации";
        else if (section == 2)
            return "Число отсчётов за раз";
        else if (section == 3)
            return "Число частот";
    }
    if (role == Qt::DisplayRole)
    {
        if (section == 0)
            return "Q";
        else if (section == 1)
            return "discr freq";
        else if (section == 2)
            return "kick count";
        else if (section == 3)
            return "freq count";
    }
    return QVariant();
}

bool ParamsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;
    return true;
}

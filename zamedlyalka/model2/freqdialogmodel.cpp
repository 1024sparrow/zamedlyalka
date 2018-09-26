#include "freqdialogmodel.h"
#include <QColor>
#include <QDebug>
#include <stdio.h>

FreqDialogModel::FreqDialogModel(struct Params *p_params, struct FreqSet *p_freqSet, QObject *parent)
    :QAbstractTableModel(parent), params(p_params), freqSet(p_freqSet)
{
//    qDebug()<<"12";
}

int FreqDialogModel::rowCount(const QModelIndex &parent) const
{
    return freqSet->count;
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
            if (section < freqSet->count)
                return QString("%1 Гц.").arg(freqSet->freq[section]);
        }
    }
    return QVariant();
}

QVariant FreqDialogModel::data(const QModelIndex &index, int role) const
{
    qDebug()<<"12";
    /*if (role == Qt::DisplayRole)
    {
        if (index.column() < 4 && index.row() < freqSet->count)
        {
            if (index.column() == 0 && (freqSet->spectra[index.row()] == (params->maxVal / 4)))
                return true;
            else if (index.column() == 1 && (freqSet->spectra[index.row()] == (2 * params->maxVal / 4)))
                return true;
            else if (index.column() == 2 && (freqSet->spectra[index.row()] == (3 * params->maxVal / 4)))
                return true;
            else if (index.column() == 3 && (freqSet->spectra[index.row()] == params->maxVal))
                return true;
            return false;
        }
    }*/
    if (role == Qt::BackgroundRole)
    {
        if (index.column() < 4 && index.row() < freqSet->count)
        {
            if (index.column() == 0 && (freqSet->spectra[index.row()] == (params->maxVal / 4)))
                ;
            else if (index.column() == 1 && (freqSet->spectra[index.row()] == (2 * params->maxVal / 4)))
                ;
            else if (index.column() == 2 && (freqSet->spectra[index.row()] == (3 * params->maxVal / 4)))
                ;
            else if (index.column() == 3 && (freqSet->spectra[index.row()] == params->maxVal))
                ;
            else
                return QColor(Qt::black);
            return QColor(Qt::yellow);
        }
    }
    return QVariant();
}

bool FreqDialogModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug()<<"12";
    if (role == Qt::EditRole)
    {
        qDebug()<<value;
        printf("asdasd");
        beginResetModel();
        int multiplier = index.column() + 1;
        double cand = params->maxVal * multiplier / 4;
        if (freqSet->spectra[index.row()] == cand)
            freqSet->spectra[index.row()] = 0;
        else
            freqSet->spectra[index.row()] = cand;
        endResetModel();
        return true;
    }
    return false;
}

Qt::ItemFlags FreqDialogModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

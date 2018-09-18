#include "mainwindow.h"
#include "freqwidget.h"
#include "normparamswidget.h"
#include "paramstablemodel.h"
#include "matrixwidget.h"

#include <QBoxLayout>
#include <QTableView>
#include <QPushButton>

MainWindow::MainWindow()
    :QWidget(0)
{
    normParams.divideFlags = 0;
    normParams.multiplyFlags = 0;

    //QTableWidget *wParams =
    QWidget *wTopPanel = new QWidget(this);
    {
        QTableView *wParams = new QTableView(wTopPanel);
        {
            ParamsTableModel *model = new ParamsTableModel((&params), wParams);
            wParams->setModel(model);
        }
        wParams->setMaximumHeight(100);
        QPushButton *bnMakeStep = new QPushButton("make step", wTopPanel);
        QBoxLayout *lay = new QHBoxLayout(wTopPanel);
        lay->addWidget(wParams);
        lay->addWidget(bnMakeStep);
    }
    QWidget *wMatrixes = new QWidget(this);
    {
        MatrixWidget *wMatrixLeft = new MatrixWidget(wMatrixes);
        MatrixWidget *wMatrixRight = new MatrixWidget(wMatrixes);
        QBoxLayout *lay = new QHBoxLayout(wMatrixes);
        lay->addWidget(wMatrixLeft);
        lay->addWidget(wMatrixRight);
    }
    QWidget *wBottomPanel = new QWidget(this);
    {
        FreqWidget *freqWidget = new FreqWidget(wBottomPanel);
        NormParamsWidget *normParamsWidget = new NormParamsWidget((&normParams), wBottomPanel);
        QBoxLayout *lay = new QHBoxLayout(wBottomPanel);
        lay->addWidget(freqWidget);
        lay->addWidget(normParamsWidget);
    }
    QBoxLayout *lay = new QVBoxLayout(this);
    lay->addWidget(wTopPanel);
    lay->addWidget(wMatrixes, 1);
    lay->addWidget(wBottomPanel);
}

#include "mainwindow.h"
#include "freqwidget.h"
#include "normparamswidget.h"
#include "paramstablemodel.h"
#include "matrixwidget.h"

#include <QBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow()
    :QWidget(0)
{
    qDebug()<<"12s";
    initFreq();
    initMatrixes();
    //~~~~~~~~~~~~~~~~~~~~~~
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
        MatrixWidget *wMatrixLeft = new MatrixWidget((&leftMatrix), wMatrixes);
        MatrixWidget *wMatrixRight = new MatrixWidget((&rightMatrix), wMatrixes);
        QBoxLayout *lay = new QHBoxLayout(wMatrixes);
        lay->addWidget(wMatrixLeft);
        lay->addWidget(wMatrixRight);
    }
    QWidget *wBottomPanel = new QWidget(this);
    {
        FreqWidget *freqWidget = new FreqWidget((&params), (&freqSet), wBottomPanel);
        NormParamsWidget *normParamsWidget = new NormParamsWidget((&normParams), wBottomPanel);
        QBoxLayout *lay = new QHBoxLayout(wBottomPanel);
        lay->addWidget(freqWidget);
        lay->addWidget(normParamsWidget, 1);
    }
    QBoxLayout *lay = new QVBoxLayout(this);
    lay->addWidget(wTopPanel);
    lay->addWidget(wMatrixes, 1);
    lay->addWidget(wBottomPanel);
}

void MainWindow::initFreq()
{
    freqSet.count = 6;
    freqSet.freq = (double *)malloc(6 * sizeof(double));
    freqSet.freq[0] = 20;
    freqSet.freq[1] = 30;
    freqSet.freq[2] = 40;
    freqSet.freq[3] = 60;
    freqSet.freq[4] = 80;
    freqSet.freq[5] = 120;
    freqSet.spectra = (double *)malloc(6 * sizeof(double));
    freqSet.spectra[0] = 0;
    freqSet.spectra[1] = 0;
    freqSet.spectra[2] = 0;
    freqSet.spectra[3] = 0;
    freqSet.spectra[4] = 0;
    freqSet.spectra[5] = 0;
}

void MainWindow::initMatrixes()
{
    size_t co = params.freqCount;

    leftMatrix.count = co;
    leftMatrix.data = new double[co * co];
    for (size_t i = 0, c = co * co ; i < c ; ++i)
    {
        leftMatrix.data[i] = i;
        leftMatrix.comments.append(QString());
    }
    leftMatrix.xLabel = "x";
    leftMatrix.yLabel = "y";

    rightMatrix.count = co;
    rightMatrix.data = new double[co * co];
    for (size_t i = 0, c = co * co ; i < c ; ++i)
    {
        rightMatrix.data[i] = i;
        rightMatrix.comments.append(QString());
    }
    rightMatrix.xLabel = "x";
    rightMatrix.yLabel = "y";
}

#include "mainwindow.h"
#include "freqwidget.h"
#include "normparamswidget.h"

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
            //
        }
        QPushButton *bnMakeStep = new QPushButton("make step", wTopPanel);
        QBoxLayout *lay = new QHBoxLayout(wTopPanel);
        lay->addWidget(wParams);
        lay->addWidget(bnMakeStep);
    }
    //
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
    lay->addWidget(wBottomPanel);
}

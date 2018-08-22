#include "mainwindow.h"
#include "test1.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QKeyEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    :QWidget(parent)
{
    process = new QProcess(this);
    connect(process, SIGNAL(aboutToClose()), this, SLOT(onProcess()));
    connect(process, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(errorOccurred(QProcess::ProcessError)));
    connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(finished(int,QProcess::ExitStatus)));
    connect(process, SIGNAL(readyReadStandardError()), this, SLOT(readyReadStandardError()));
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
    connect(process, SIGNAL(started()), this, SLOT(started()));
    connect(process, SIGNAL(stateChanged(QProcess::ProcessState)), this, SLOT(stateChanged(QProcess::ProcessState)));
    process->start("./zamedlyalka");
    if (!process->waitForStarted(3000))
    {
        qDebug()<<"can't start";
    }
    qDebug()<<"started";
    // -----------
    QBoxLayout *mainLay = new QHBoxLayout(this);
    QWidget *leftsidePanel = new QWidget(this);
    {
        QPushButton *bn1 = new QPushButton("generator", this);
        QBoxLayout *lay = new QVBoxLayout(leftsidePanel);
        lay->addWidget(bn1);
    }
    QStackedWidget *gameplayArea = new QStackedWidget(this);
    {
        QWidget *t1 = new Test1(gameplayArea);
        gameplayArea->addWidget(t1);
    }
    mainLay->addWidget(leftsidePanel);
    mainLay->addWidget(gameplayArea);
}

void MainWindow::onBn1Clicked()
{
    //
}

void MainWindow::onProcess()
{
    qDebug()<<"onProcess";
}

void MainWindow::errorOccurred(QProcess::ProcessError error)
{
    qDebug()<<"errorOccurred";
}

void MainWindow::finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug()<<"finished";
}

void MainWindow::readyReadStandardError()
{
    qDebug()<<"readyReadStandardError";
}

void MainWindow::readyReadStandardOutput()
{
    //qDebug()<<"readyReadStandardOutput";
    qDebug()<<process->readAllStandardOutput();
}

void MainWindow::started()
{
    qDebug()<<"started";
}

void MainWindow::stateChanged(QProcess::ProcessState newState)
{
    qDebug()<<"stateChanged";
}

int transformKeyCode(int p)
{
    qDebug()<<"qt key code: "<<p;
    switch (p){
    case 16777216: return 27; // <ESC>
    case 81: return 113; // q
    case 87: return 119; // w
    case 69: return 101; // e
    case 82: return 114; // r
    case 84: return 116; // t
    case 89: return 121; // y
    case 85: return 117; // u
    case 73: return 105; // i
    case 79: return 111; // o
    case 80: return 112; // p
    case 65: return 97; // a
    case 83: return 115; // s
    case 68: return 100; // d
    case 70: return 102; // f
    case 71: return 103; // g
    case 72: return 104; // h
    case 74: return 106; // j
    case 75: return 107; // k
    case 76: return 108; // l
    case 90: return 122; // z
    case 88: return 120; // x
    case 67: return 99; // c
    case 86: return 118; // v
    case 66: return 98; // b
    case 78: return 110; // n
    case 77: return 109; // m
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"key pressed: "<<event->text();
    int k = transformKeyCode(event->key());
    process->write("q");
//    process->closeWriteChannel();
    //if (k)
}

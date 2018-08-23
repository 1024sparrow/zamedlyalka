#include "mainwindow.h"
#include "test1.h"
#include <stdio.h>

#include <QHBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QKeyEvent>
#include <QTextStream>
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
   // process->start("./zamedlyalka__mplayer_bash");
    if (!process->waitForStarted(3000))
    {
        qDebug()<<"can't start";
    }
    qDebug()<<"__khgkjhgkjhgjhg";
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
    printf("onProcess (about to close)\n");
}

void MainWindow::errorOccurred(QProcess::ProcessError error)
{
    printf("errorOccurred\n");
}

void MainWindow::finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    printf("finished\n");
    exit(0);
}

void MainWindow::readyReadStandardError()
{
    printf("readyReadStandardError\n");
    QByteArray ba = process->readAllStandardError();
    printf(ba.toStdString().c_str());
}

void MainWindow::readyReadStandardOutput()
{
    printf("readyReadStandardOutput\n");
    QByteArray ba = process->readAllStandardOutput();
    printf(ba.toStdString().c_str());
}

void MainWindow::started()
{
    printf("started\n");
}

void MainWindow::stateChanged(QProcess::ProcessState newState)
{
    //printf("stateChanged\n");
}
const char * transformKeyCode(int p)
{
    qDebug()<<"qt key code: "<<p;
    switch (p){
    case 16777216: return "quit\n"; // <ESC>
    case 81: return "q\n"; // q
    case 87: return "w\n"; // w
    case 69: return "e\n"; // e
    case 82: return "r\n"; // r
    case 84: return "t\n"; // t
    case 89: return "y\n"; // y
    case 85: return "u\n"; // u
    case 73: return "i\n"; // i
    case 79: return "o\n"; // o
    case 80: return "p\n"; // p
    case 65: return "a\n"; // a
    case 83: return "s\n"; // s
    case 68: return "d\n"; // d
    case 70: return "f\n"; // f
    case 71: return "g\n"; // g
    case 72: return "h\n"; // h
    case 74: return "j\n"; // j
    case 75: return "k\n"; // k
    case 76: return "l\n"; // l
    case 90: return "z\n"; // z
    case 88: return "x\n"; // x
    case 67: return "c\n"; // c
    case 86: return "v\n"; // v
    case 66: return "b\n"; // b
    case 78: return "n\n"; // n
    case 77: return "m\n"; // m
    default: return NULL;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    const char * k = transformKeyCode(event->key());
    //printf("key pressed: %s(%i)\n", event->text().toStdString().c_str(), k);
    //printf("----key pressed: %s\n", k);
    if (k != NULL)
        process->write(k);
    //QTextStream stream(process);
    //stream << "qwer";
    //stream.setDevice(process);
//    process->closeWriteChannel();
    //if (k)
}

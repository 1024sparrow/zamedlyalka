#include "mainwindow.h"
#include "test1.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
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
    qDebug()<<"readyReadStandardOutput";
}

void MainWindow::started()
{
    qDebug()<<"started";
}

void MainWindow::stateChanged(QProcess::ProcessState newState)
{
    qDebug()<<"stateChanged";
}

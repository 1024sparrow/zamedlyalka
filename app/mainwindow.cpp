#include "mainwindow.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    :QWidget(parent)
{
    QBoxLayout *mainLay = new QHBoxLayout(this);
    QWidget *leftsidePanel = new QWidget(this);
    {
        QPushButton *bn1 = new QPushButton("generator", this);
        QBoxLayout *lay = new QVBoxLayout(leftsidePanel);
        lay->addWidget(bn1);
    }
    QStackedWidget *gameplayArea = new QStackedWidget(this);
    {
        //
    }
    mainLay->addWidget(leftsidePanel);
    mainLay->addWidget(gameplayArea);

}

void MainWindow::onBn1Clicked()
{
    //
}

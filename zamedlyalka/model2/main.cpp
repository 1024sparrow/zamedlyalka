#include <QApplication>

#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow *mw = new MainWindow();
    //mw.showMaximized();
    mw->show();
    app.exec();
}

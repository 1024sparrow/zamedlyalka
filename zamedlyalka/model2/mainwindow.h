#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "types.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow();

private:
    struct NormParams normParams;
    struct Params params;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "types.h"
#include "matrix_data.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow();
private:
    void initFreq();

private:
    struct NormParams normParams;
    struct Params params;
    struct FreqSet freqSet;
    struct MatrixData leftMatrix, rightMatrix;
};

#endif // MAINWINDOW_H

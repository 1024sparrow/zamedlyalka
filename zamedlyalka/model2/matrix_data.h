#ifndef MATRIX_DATA_H
#define MATRIX_DATA_H

#include <QStringList>

#define MATRIXDATA_COMMENT_BUF_LENGTH 512

// Квадратная матрица неотрицательный значений
//data и comments: заполнение по столбцам
struct MatrixData
{
    char *xLabel;
    char *yLabel;
    size_t count;
    double *data;
    //char *comments;
    QStringList comments;
    //char **comm;
    double maxVal;
};

#endif // MATRIX_DATA_H

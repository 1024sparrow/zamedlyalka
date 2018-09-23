#ifndef MATRIX_DATA_H
#define MATRIX_DATA_H

#define MATRIXDATA_COMMENT_BUF_LENGTH 512

// Квадратная матрица
//data и comments: заполнение по столбцам
struct MatrixData
{
    char *xLabel;
    char *yLabel;
    size_t count;
    double *data;
    char *comments;
};

#endif // MATRIX_DATA_H

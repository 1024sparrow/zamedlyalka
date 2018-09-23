#ifndef MATRIXWIDGET_H
#define MATRIXWIDGET_H

#include <QWidget>
#include "matrix_data.h"

// Виджет отображения квадратной матрицы
class MatrixWidget : public QWidget
{
    Q_OBJECT
public:
    MatrixWidget(struct MatrixData *p_md, QWidget *parent = 0);

private:
    struct MatrixData *md;
};

#endif // MATRIXWIDGET_H

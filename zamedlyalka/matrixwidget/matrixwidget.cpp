#include "matrixwidget.h"

MatrixWidget::MatrixWidget(MatrixData *p_md, QWidget *parent)
    :QWidget(parent), md(p_md)
{
    setMinimumSize(500,500);

}

#include "matrixwidget.h"

#include <QPainter>

MatrixWidget::MatrixWidget(QWidget *parent)
    :QWidget(parent)
{
    setMinimumSize(256,256);

}

void MatrixWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::yellow);
}

#ifndef MATRIXWIDGET_H
#define MATRIXWIDGET_H

#include <QWidget>
#include <QList>
#include "matrix_data.h"

class QPaintEvent;
class QResizeEvent;
class QMouseEvent;

class MatrixWidgetItem;

// Виджет отображения квадратной матрицы
class MatrixWidget : public QWidget
{
    Q_OBJECT
public:
    MatrixWidget(struct MatrixData *p_md, QWidget *parent = 0);
    void update();
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    struct MatrixData *md;
    int displayMode;

    QList<MatrixWidgetItem *> wwItems;
    size_t matrixSizePrev;
};

#endif // MATRIXWIDGET_H

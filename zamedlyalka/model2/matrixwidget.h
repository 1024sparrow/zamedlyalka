#ifndef MATRIXWIDGET_H
#define MATRIXWIDGET_H

#include <QWidget>

class QPaintEvent;
class MatrixWidget : public QWidget
{
    Q_OBJECT
public:
    MatrixWidget(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // MATRIXWIDGET_H

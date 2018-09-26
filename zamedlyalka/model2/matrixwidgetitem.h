#ifndef MATRIXWIDGETITEM_H
#define MATRIXWIDGETITEM_H

#include <QWidget>
#include "matrix_data.h"

class MatrixWidgetItem : public QWidget
{
    Q_OBJECT
public:
    MatrixWidgetItem(int *p_displayMode, size_t p_x, size_t p_y, struct MatrixData *p_matrixData, QWidget *parent = 0);
    ~MatrixWidgetItem();
    void update();
protected:
    void paintEvent(QPaintEvent *event);

private:
    size_t x, y, index;
    struct MatrixData *matrixData;
    int *displayMode;

    char *tooltipPrev;
    double valuePrev;
    double maxPrev;
    int displayModePrev;
};

#endif // MATRIXWIDGETITEM_H

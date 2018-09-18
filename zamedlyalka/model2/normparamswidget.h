#ifndef NORMPARAMSWIDGET_H
#define NORMPARAMSWIDGET_H

#include <QWidget>
#include "types.h"

class QPaintEvent;
class QMouseEvent;
class NormParamsWidget : public QWidget
{
    Q_OBJECT
public:
    NormParamsWidget(struct NormParams *p_normParams, QWidget *parent = 0);
signals:
    void changed();
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    struct NormParams *normParams;
};

#endif // NORMPARAMSWIDGET_H

#include "normparamswidget.h"

#include <QPainter>
#include <QMouseEvent>

NormParamsWidget::NormParamsWidget(NormParams *p_normParams, QWidget *parent)
    :QWidget(parent), normParams(p_normParams)
{
    setMinimumSize(400, 100);
}

void NormParamsWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int w = width();
    int h = height();

    QRgb COLOR_MULTIPLIER = 0x4488ff;
    QRgb COLOR_DIVIDER = 0xff8800;
    QRgb COLOR_NEUTRAL = 0xffffff;


    const QRect rc11(0,0,w/3, h/2);
    const QRect rc12(w/3,0,w/3, h/2);
    const QRect rc13(2*w/3,0,w/3, h/2);
    const QRect rc21(0,h/2,w/3, h/2);
    const QRect rc22(w/3,h/2,w/3, h/2);
    const QRect rc23(2*w/3,h/2,w/3, h/2);

    QRgb col11 = normParams->multiplyFlags & NormParams__Variants__devR2 ? COLOR_MULTIPLIER : (normParams->divideFlags & NormParams__Variants__devR2 ? COLOR_DIVIDER : COLOR_NEUTRAL);
    QRgb col21 = normParams->multiplyFlags & NormParams__Variants__devR1 ? COLOR_MULTIPLIER : (normParams->divideFlags & NormParams__Variants__devR1 ? COLOR_DIVIDER : COLOR_NEUTRAL);
    QRgb col12 = normParams->multiplyFlags & NormParams__Variants__sinusDevR2 ? COLOR_MULTIPLIER : (normParams->divideFlags & NormParams__Variants__sinusDevR2 ? COLOR_DIVIDER : COLOR_NEUTRAL);
    QRgb col22 = normParams->multiplyFlags & NormParams__Variants__sinusDevR1 ? COLOR_MULTIPLIER : (normParams->divideFlags & NormParams__Variants__sinusDevR1 ? COLOR_DIVIDER : COLOR_NEUTRAL);
    QRgb col13 = normParams->multiplyFlags & NormParams__Variants__sinResDevR2 ? COLOR_MULTIPLIER : (normParams->divideFlags & NormParams__Variants__sinResDevR2 ? COLOR_DIVIDER : COLOR_NEUTRAL);
    QRgb col23 = normParams->multiplyFlags & NormParams__Variants__sinResDevR1 ? COLOR_MULTIPLIER : (normParams->divideFlags & NormParams__Variants__sinResDevR1 ? COLOR_DIVIDER : COLOR_NEUTRAL);

    painter.fillRect(rc11, col11);
    painter.fillRect(rc12, col12);
    painter.fillRect(rc13, col13);
    painter.fillRect(rc21, col21);
    painter.fillRect(rc22, col22);
    painter.fillRect(rc23, col23);
    QTextOption to(Qt::AlignCenter);
    painter.drawText(rc11, "dev R2", to);
    painter.drawText(rc12, "sinus dev R2", to);
    painter.drawText(rc13, "sinus resonance dev R2", to);
    painter.drawText(rc21, "dev R1", to);
    painter.drawText(rc22, "sinus dev R1", to);
    painter.drawText(rc23, "abc", to);
    painter.drawRect(0, 0, w - 1, h - 1);
    painter.drawLine(w/3, 0, w/3, h);
    painter.drawLine(2*w/3, 0, 2*w/3, h);
    painter.drawLine(0, h/2, w, h/2);
}

void NormParamsWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    int w = width();
    int h = height();
    int targetFlag = 0;
    if (pos.y() < h/2)
    {
        if (pos.x() < w/3)
            targetFlag = NormParams__Variants__devR2;
        else if (pos.x() < 2*w/3)
            targetFlag = NormParams__Variants__sinusDevR2;
        else
            targetFlag = NormParams__Variants__sinResDevR2;
    }
    else
    {
        if (pos.x() < w/3)
            targetFlag = NormParams__Variants__devR1;
        else if (pos.x() < 2*w/3)
            targetFlag = NormParams__Variants__sinusDevR1;
        else
            targetFlag = NormParams__Variants__sinResDevR1;
    }
    if (event->buttons() & Qt::LeftButton)
        normParams->toggle(targetFlag, false);
    else if (event->buttons() & Qt::RightButton)
        normParams->toggle(targetFlag, true);
    else
        return;
    if (isVisible())
        repaint();
}

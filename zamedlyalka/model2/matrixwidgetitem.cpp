#include "matrixwidgetitem.h"

#include <QPainter>
#include <QStringList>
#include <QString>
#include <qmath.h>

MatrixWidgetItem::MatrixWidgetItem(int *p_displayMode, size_t p_x, size_t p_y, MatrixData *p_matrixData, QWidget *parent)
    :QWidget(parent), displayMode(p_displayMode), x(p_x), y(p_y), matrixData(p_matrixData)
{
    tooltipPrev = (char *)(malloc(MATRIXDATA_COMMENT_BUF_LENGTH * sizeof(char)));
    index = p_x * p_matrixData->count + p_y;
    update();
}

MatrixWidgetItem::~MatrixWidgetItem()
{
    free(tooltipPrev);
}

void MatrixWidgetItem::update()
{
    //if (strncmp((const char *)tooltipPrev, (const char *)matrixData->comments[index], MATRIXDATA_COMMENT_BUF_LENGTH) == 0)
    {
        //setToolTip("asdfsdf");
        QString tooltipText = QString("x: %1\ny: %2\nvalue: %3")
                .arg(matrixData->xLabel)
                .arg(matrixData->yLabel)
                .arg(matrixData->data[index]);
        if (!matrixData->comments[index].isEmpty())
        {
            tooltipText.append("\n==========\n");
            tooltipText.append(matrixData->comments[index]);
        }
        setToolTip(tooltipText);
        //strncpy(tooltipPrev, matrixData->comments + index, 2);//MATRIXDATA_COMMENT_BUF_LENGTH);
        //strncpy(tooltipPrev, (const char *)matrixData->comments[index], 2);//MATRIXDATA_COMMENT_BUF_LENGTH);

        //const char *

        //tooltipPrev[MATRIXDATA_COMMENT_BUF_LENGTH - 1] = '\0';
        //setToolTip(tooltipPrev);
    }
    int changed = 0;
    if (matrixData->data[index] != valuePrev)
    {
        valuePrev = matrixData->data[index];
        changed = 1;
    }
    if (matrixData->maxVal != maxPrev)
    {
        maxPrev = matrixData->maxVal;
        changed = 1;
    }
    if ((*displayMode) != displayModePrev)
    {
        displayModePrev = (*displayMode);
        changed = 1;
    }
    if (changed)
    {
        if (isVisible())
            repaint();
    }

    //if (isVisible())
    //    repaint();
}

void MatrixWidgetItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (matrixData->maxVal == 0)
    {
        return;
    }
    //painter.fillRect(rect(), QColor(qrand() % 256, qrand() % 256, qrand() % 256));
    int valueNormed = matrixData->data[index] * 256 / matrixData->maxVal;
    QColor color(255,255,170); // #ffa
    if ((*displayMode) == 0)
    {
        //color.setHsv(0, 0, qSqrt(valueNormed * 256));
        color.setHsv(0, 0, (qSqrt(valueNormed * 256) + 255 - qSqrt(256*(255 - valueNormed)))/2);
    }
    /*else if ((*displayMode) == 1)
    {
        color.setHsv(0, 0, 255 - qSqrt(256*(255 - valueNormed)));
    }
    else if ((*displayMode) == 2)
    {
        color.setHsv(0, 0, qSqrt(valueNormed * 256));
    }*/
    else if ((*displayMode) == 1)
    {
        valueNormed = matrixData->data[index] * 200. / matrixData->maxVal;
        if (valueNormed < 50)
            color.setHsv(240, 255, 55+valueNormed * 4);
        else if (valueNormed < 100)
            color.setHsv(60, 255, 55 + (valueNormed - 50) * 4);
        else if (valueNormed < 150)
            color.setHsv(0, 255, 55 + (valueNormed - 100) * 4);
        else
            color.setHsv(0, 0, 55 + (valueNormed - 150) * 4);
    }

    painter.fillRect(rect(), color);
}

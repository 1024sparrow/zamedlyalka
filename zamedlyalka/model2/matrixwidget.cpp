#include "matrixwidget.h"
#include "matrixwidgetitem.h"

#include <QPainter>
#include <QMessageBox>//

MatrixWidget::MatrixWidget(MatrixData *p_md, QWidget *parent)
    :QWidget(parent), md(p_md), displayMode(0)
{
    setMinimumSize(500,500);
    update();
}

void MatrixWidget::update()
{
    md->maxVal = 0;
    for (size_t i = 0, c = md->count * md->count ; i < c ; ++i)
    {
        if (md->data[i] > md->maxVal)
            md->maxVal = md->data[i];
    }
    if (matrixSizePrev != md->count)
    {
        if (!wwItems.isEmpty())
        {
            foreach (MatrixWidgetItem *i, wwItems)
            {
                delete i;
            }
        }
        wwItems.clear();
        matrixSizePrev = md->count;

        for (size_t iX = 0 ; iX < md->count ; ++iX)
        {
            for (size_t iY = 0 ; iY < md->count ; ++iY)
            {
                MatrixWidgetItem *item = new MatrixWidgetItem((&displayMode), iX, iY, md, this);
                wwItems.append(item);
            }
        }
    }
    size_t counter = 0;
    int itemSize = qMin(width(), height()) / md->count;
    if (itemSize > 0)
    {
        for (size_t iX = 0 ; iX < md->count ; ++iX)
        {
            for (size_t iY = 0 ; iY < md->count ; ++iY)
            {
                MatrixWidgetItem *item = wwItems[counter];
                item->setFixedSize(itemSize, itemSize);
                item->move(iX * itemSize, iY * itemSize);
                counter++;
            }
        }
    }
}

void MatrixWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(Qt::Dense7Pattern);
    painter.drawRect(0,0,width() - 1, height() - 1);
    //painter.drawLine(0,0,width(), height());
    //painter.drawLine(0,height(), width(), 0);
}

void MatrixWidget::resizeEvent(QResizeEvent *event)
{
    update();
}

void MatrixWidget::mousePressEvent(QMouseEvent *event)
{
    //QMessageBox::information(0, "", "asdfghjk");
    displayMode = (++displayMode) % 2; // четыре режима отображения цветом
    foreach (MatrixWidgetItem *i, wwItems) {
        i->update();
    }
}

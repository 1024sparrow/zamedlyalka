#include "matrixwidget.h"
#include "matrixwidgetitem.h"

#include <QMessageBox>//

MatrixWidget::MatrixWidget(MatrixData *p_md, QWidget *parent)
    :QWidget(parent), md(p_md), displayMode(0)
{
    setMinimumSize(500,500);
    update();
}

void MatrixWidget::update()
{
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
    int itemSize = width() / md->count;
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

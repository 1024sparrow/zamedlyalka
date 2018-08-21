#include "test1.h"
#include <QHBoxLayout>
#include <QPushButton>

Test1::Test1(QWidget *parent)
    :QWidget(parent)
{
    QPushButton *bnPlay = new QPushButton("play", this);
    QPushButton *bnStop = new QPushButton("stop", this);
    QBoxLayout *lay = new QVBoxLayout(this);
    lay->addWidget(bnPlay);
    lay->addWidget(bnStop);
}

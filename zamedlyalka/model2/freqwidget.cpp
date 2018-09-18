#include "freqwidget.h"

#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>

FreqWidget::FreqWidget(QWidget *parent)
    :QWidget(parent)
{
    m_label = new QLabel(this);
    QPushButton *bn = new QPushButton("edit", this);
    QBoxLayout *lay = new QHBoxLayout(this);
    lay->addWidget(m_label);
    lay->addWidget(bn);

}

#include "freqwidget.h"
#include "freqdialogmodel.h"

#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPainter>
#include <QDialog>
#include <QTableView>
#include <QMessageBox>//

FreqWidget::FreqWidget(struct Params *p_params, struct FreqSet *p_freqSet, QWidget *parent)
    :QWidget(parent), params(p_params), freqSet(p_freqSet)
{
    m_label = new QLabel(this);
    QPushButton *bn = new QPushButton("edit", this);
    connect(bn, SIGNAL(pressed()), this, SLOT(onBnEditClicked()));
    QBoxLayout *lay = new QHBoxLayout(this);
    lay->addWidget(m_label);
    lay->addWidget(bn);

}

void FreqWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::red);
}

void FreqWidget::onBnEditClicked()
{
    struct FreqSet freqSetCopy = {
        freqSet->count,
        freqSet->freq, // сами частоты мы не меняем
        (double*)malloc(freqSet->count * sizeof(double))
    };
    memcpy(freqSetCopy.spectra, freqSet->spectra, freqSet->count * sizeof(double));
    QDialog dlg(this);
    {
        dlg.setMinimumSize(800,600);
        QTableView *tv = new QTableView(&dlg);
        {
            FreqDialogModel *model = new FreqDialogModel(params, (&freqSetCopy), tv);
            tv->setModel(model);
        }
        QWidget *wButtons = new QWidget(&dlg);
        {
            QPushButton *bnOk = new QPushButton("Применить", wButtons);
            connect(bnOk, SIGNAL(pressed()), &dlg, SLOT(accept()));
            QPushButton *bnCancel = new QPushButton("Вернуться", wButtons);
            connect(bnCancel, SIGNAL(pressed()), &dlg, SLOT(reject()));
            QBoxLayout *lay = new QHBoxLayout(wButtons);
            lay->addStretch();
            lay->addWidget(bnOk);
            lay->addWidget(bnCancel);
        }
        QBoxLayout *lay = new QVBoxLayout(&dlg);
        lay->addWidget(tv);
        lay->addWidget(wButtons);
    }
    if (dlg.exec() != QDialog::Accepted)
        return;
    memcpy(freqSet->spectra, freqSetCopy.spectra, freqSet->count * sizeof(double));
    free(freqSetCopy.spectra);
}

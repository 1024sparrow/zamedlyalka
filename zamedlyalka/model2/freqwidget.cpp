#include "freqwidget.h"
#include "freqdialogmodel.h"

#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPainter>
#include <QDialog>
#include <QTableView>
#include <QPalette>

FreqWidget::FreqWidget(struct Params *p_params, struct FreqSet *p_freqSet, QWidget *parent)
    :QWidget(parent), params(p_params), freqSet(p_freqSet)
{
    setMinimumWidth(300);

    m_label = new QLabel(this);
    //QPushButton *bn = new QPushButton("edit", this);
    //connect(bn, SIGNAL(pressed()), this, SLOT(onBnEditClicked()));
    QBoxLayout *lay = new QHBoxLayout(this);
    lay->setMargin(0);
    lay->addWidget(m_label);
    //lay->addWidget(bn);
    updateForData();

    m_label->setStyleSheet("color:#ffa;background:#000;padding: 20px;");
}

void FreqWidget::updateForData()
{
    QString text;
    for (int i = 0 ; i < freqSet->count ; ++i)
    {
        if (freqSet->spectra[i] == 0)
            continue;
        if (!text.isEmpty())
            text.append("\n");
        text.append(QString("%1 Гц.: %2").arg(freqSet->freq[i]).arg(freqSet->spectra[i]));
    }
    if (text.isEmpty())
        text = "входного сигнала нет!";
    m_label->setText(text);
}

void FreqWidget::mousePressEvent(QMouseEvent *event)
{
    onBnEditClicked();
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
    updateForData();
}

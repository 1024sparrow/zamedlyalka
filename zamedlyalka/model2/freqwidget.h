#ifndef FREQWIDGET_H
#define FREQWIDGET_H

#include <QWidget>
#include "types.h"

class QLabel;
class QPaintEvent;
class FreqWidget : public QWidget
{
    Q_OBJECT
public:
    FreqWidget(struct Params *p_params, struct FreqSet *p_freqSet, QWidget *parent = 0);
signals:
    void changed(); // changed freqSet
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void onBnEditClicked();

private:
    QLabel *m_label;
    struct Params *params;
    struct FreqSet *freqSet;
};

#endif // FREQWIDGET_H

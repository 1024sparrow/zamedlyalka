#ifndef FREQWIDGET_H
#define FREQWIDGET_H

#include <QWidget>

class QLabel;
class FreqWidget : public QWidget
{
    Q_OBJECT
public:
    FreqWidget(QWidget *parent = 0);

private:
    QLabel *m_label;
};

#endif // FREQWIDGET_H

#ifndef MW_H
#define MW_H

#include <QWidget>
#include <sys/types.h>

class QLineEdit;
class MW : public QWidget
{
    Q_OBJECT
public:
    MW();
private slots:
    void onStartBnClicked();
private:
    void process(double p_wholeTime, double p_discretFreq,
                 size_t &pout_count, double *&pout_array, double *&pout_timeArray);

    double time_whole;
    QLineEdit *leWholeTime;
    QLineEdit *leDicretFreq;
};

#endif // MW_H

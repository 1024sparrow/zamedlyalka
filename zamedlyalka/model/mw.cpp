#include "mw.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include <QBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QList>
#include <QFrame>
#include <QProcess>

//buttons

MW::MW()
    :QWidget(0)
{
    QWidget *wCanvas = new QFrame(this);
    {
        //
    }
    QWidget *wParams = new QFrame(this);
    {
        QWidget * wWholeTime = new QWidget(wParams);
        {
            leWholeTime = new QLineEdit(wWholeTime);
            leDicretFreq = new QLineEdit(wWholeTime);
            QFormLayout *lay = new QFormLayout(wWholeTime);
            lay->addRow("while time (ms):", leWholeTime);
            lay->addRow("discret freq (Hz):", leDicretFreq);
        }
        QBoxLayout *lay = new QHBoxLayout(wParams);
        lay->addWidget(wWholeTime);
    }
    QWidget *wButtons = new QFrame(this);
    {
        QPushButton *bnStart = new QPushButton("Start", wButtons);
        connect(bnStart, SIGNAL(pressed()), this, SLOT(onStartBnClicked()));
        QPushButton *bnQuit = new QPushButton("Quit", wButtons);
        connect(bnQuit, SIGNAL(pressed()), this, SLOT(close()));
        QBoxLayout *lay = new QHBoxLayout(wButtons);
        lay->addStretch();
        lay->addWidget(bnStart);
        lay->addWidget(bnQuit);
    }
    QBoxLayout *lay = new QVBoxLayout(this);
    lay->addWidget(wCanvas, 1);
    lay->addWidget(wParams);
    lay->addWidget(wButtons);
}

void MW::onStartBnClicked()
{
    double wholeTime = leWholeTime->text().toDouble();
    double discretFreq = leDicretFreq->text().toDouble();
    // ... (получаем массив данных)
    /*
     * 1. Получаем массив данных
     * 2. Записываем данные в файл data.dat
     * 3. Запускаем (синхронно) gnuplot. Пусть gnuplot читает данные из data.dat и пишет svg-картинку в image.svg
     * 4. Обновляем отображение нашей отображалки SVG-файла wCanvas.
     */
    size_t sz = 0;
    double *array, *timeArray;
    process(wholeTime, discretFreq, sz, array, timeArray);

    int fdDat = open("data.dat",  O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);
    const char *h = "#t i\n";
    write(fdDat, h, strlen(h));
    for (size_t i = 0 ; i < sz ; i++)
    {
        dprintf(fdDat, "%f %f\n", timeArray[i], array[i]);
    }
    ::close(fdDat);

    // fork -> execute "gnuplot plot.plt" into "bin/"
    //QProcess pr;
}

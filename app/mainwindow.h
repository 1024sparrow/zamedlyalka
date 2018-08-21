#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
class QStackedWidget;

class MainWindow : public QWidget
{
public:
    MainWindow(QWidget *parent = 0);

private slots:
    void onBn1Clicked();

private:
    QStackedWidget *gameplayArea;

};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QProcess>
class QStackedWidget;
class QKeyEvent;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);

private slots:
    void onBn1Clicked();
    void onProcess();

    void errorOccurred(QProcess::ProcessError error);
    void finished(int exitCode, QProcess::ExitStatus exitStatus);
    void readyReadStandardError();
    void readyReadStandardOutput();
    void started();
    void stateChanged(QProcess::ProcessState newState);
private:
    void keyPressEvent(QKeyEvent *event);


private:
    QStackedWidget *gameplayArea;
    QProcess *process;

};

#endif // MAINWINDOW_H

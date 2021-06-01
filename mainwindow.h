#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_initButton_clicked();

    void on_sendCommand_clicked();

    void on_activatePort1_clicked();

    void on_deactivatePort1_clicked();

    void on_testSioxData_clicked();

    void on_testSioxTextEx_clicked();

private:
    void log(QString message);
    void log(bool sent, std::vector<int> message);
    QString hexstr(int n);
    std::vector<int> parseHexString(QString input);

    Ui::MainWindow *ui;
    Controller hw;
};
#endif // MAINWINDOW_H

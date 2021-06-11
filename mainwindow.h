#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
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

    void on_testSioxText_clicked();

    void on_testRAMWrite_clicked();

    void on_readRAMButton_clicked();

    void on_testRAMStuffButton_clicked();

    void on_writeValueButton_clicked();

    void on_setBitButton_clicked();

private:
    void log(QString message);
    void log(bool sent, std::vector<int> message);
    QString hexstr(int n);
    std::vector<int> parseHexStrings(QString input);
    int parseHexString(QString input);
    void dumpParameters(std::vector<uint16_t> data, QTextEdit *outputTextEdit);
    void dumpParametersAsHex(std::vector<uint16_t> data, QTextEdit *outputTextEdit);
    void eepromDump();
    void eepromDump(std::vector<uint16_t> data);
    void readData(int startAddress, int lastAddress, QTextEdit *outputTextEdit, bool readRam, bool outputHex);

    void activatePort(int portNumber);
    void deactivatePort(int portNumber);
    void setPortState(int portNumber, int state);

    Ui::MainWindow *ui;
    Controller hw;
};
#endif // MAINWINDOW_H

#include <Siox30.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpression>
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->log->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::log(QString message)
{
    auto log = ui->log;
    auto contents = log->toPlainText();
    contents += message;
    contents += "\n";
    log->setText(contents);
}

void MainWindow::log(bool sent, std::vector<int> message)
{
    QString str = sent ? "-->  " : "<--  ";

    for (int n : message) {
        str += hexstr(n);
        str += " ";
    }

    log(str);
}

QString MainWindow::hexstr(int n)
{
    QString hexdigits{ "0123456789ABCDEF" };
    QString result = "0x";

    result += hexdigits[(n & 0b11110000) >> 4];
    result += hexdigits[n & 0b00001111];

    return result;
}

void MainWindow::on_initButton_clicked()
{
    QString port = ui->portTextbox->text();
    int speed = ui->speedTextbox->text().toInt();
    bool initialized = hw.init(port, speed);

    if (initialized) {
        log("Init succeded");
        QString busNumber = QString::asprintf("%d", hw.bus);
        ui->busNumberLabel->setText(busNumber);
    } else {
        log("Init failed");
        log(hw.getErrorMessage());
    }
}

std::vector<int> MainWindow::parseHexString(QString input)
{
    if (input.length() == 0) return {};

    std::vector<int> result;
    QStringList list;
    bool ok;

    list = input.split(QRegularExpression("\\s+"));

    for (int i = 0; i < list.length(); ++i) {
        int hex = (int) list[i].toUInt(&ok, 16);
        if (ok)
            result.push_back(hex);
    }

    return result;
}

void MainWindow::on_sendCommand_clicked()
{
    QString input = ui->commandTextbox->text();
    std::vector<int> command = parseHexString(input);

    log(true, command);
    std::vector<int> response = hw.send(command);
    log(false, response);

    QString result = hw.result();

    if (result.length() > 0) log(result);
}

void MainWindow::on_activatePort1_clicked()
{
    std::vector<int> command{ 0xc1, 0x01 };

    log("Activating port 1");
    log(true, command);
    std::vector<int> response = hw.send(command);
    log(false, response);

    QString result = hw.result();

    if (result.length() > 0) log(result);
}

void MainWindow::on_deactivatePort1_clicked()
{
    std::vector<int> command{ 0xc1, 0x00 };

    log("Deactivating port 1");
    log(true, command);
    std::vector<int> response = hw.send(command);
    log(false, response);

    QString result = hw.result();

    if (result.length() > 0) log(result);
}

void MainWindow::on_testSioxData_clicked()
{
    if (ui->outputTextBox->text().length() == 0) return;
    if (ui->stationAddressTextBox->text().length() == 0) return;

    int *input = new int[50];
    std::vector<int> outputs = parseHexString(ui->outputTextBox->text());
    int output = outputs[0];
    int outputCount = 1;
    int bus = hw.bus;
    unsigned int stationAddress = ui->stationAddressTextBox->text().toInt();
    int silent;

    QString text = QString::asprintf("SioxData bus %d address %d output 0x%x", bus, stationAddress, output);
    log(text);
    SioxData(bus, stationAddress, output, outputCount, input, &silent);
    text = QString::asprintf("Input:\t%s\nInputCount:\t%d\nSilent:\t%d\nBusy:\t%d\n", input, silent);

    delete[] input;
}

void MainWindow::on_testSioxTextEx_clicked()
{
    if (ui->outputTextBox->text().length() == 0) return;
    if (ui->groupAddressTextBox->text().length() == 0) return;
    if (ui->stationAddressTextBox->text().length() == 0) return;

    std::vector<int> outputs = parseHexString(ui->outputTextBox->text());
    int outputCount = outputs.size();
    char *output = new char[outputCount + 1];
    char *input = new char[50];
    int inputCount;
    int bus = hw.bus;
    unsigned int groupAddress = ui->groupAddressTextBox->text().toInt();
    unsigned int stationAddress = ui->stationAddressTextBox->text().toInt();
    int numbered = 0;
    int silent;
    int busy;

    for (int i = 0; i < outputCount; ++i)
        output[i] = (char) outputs[i];
    output[outputCount] = '\0';

    QString text = QString::asprintf("SioxTextEx bus %d groupAddress %d stationAddress %d output ", bus, groupAddress, stationAddress);

    for (int i = 0; i < outputCount; ++i)
        text += QString::asprintf("0x%x ", output[i]);

    log(text);
    SioxTextEx(bus, groupAddress, stationAddress, output, outputCount, input, &inputCount, numbered, &silent, &busy);
    text = QString::asprintf("Input:\t%s\nInputCount:\t%d\nSilent:\t%d\nBusy:\t%d\n", input, inputCount, silent, busy);

    delete[] output;
    delete[] input;
}


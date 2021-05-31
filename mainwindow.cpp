#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpression>

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

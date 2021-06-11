#include <Siox30.h>

#include <Windows.h>
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
    ui->addressLCD->setMode(QLCDNumber::Hex);
    eepromDump();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::eepromDump()
{
    std::vector<uint16_t> data {
        0x0801, 0x0100, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0xAA48, 0xA120, 0xAA44, 0xA213, 0xAA48, 0xA20E, 0xA020, 0xA444,
        0xA630, 0x50AA, 0x40A8, 0x3014, 0x0D22, 0xA023, 0xA640, 0xA648,
        0x60A6, 0x44AA, 0x54A1, 0x43AA, 0x50A2, 0x36AA, 0x54A2, 0x31A0,
        0x43A4, 0x50A6, 0x3251, 0xAA4C, 0xA832, 0x140D, 0x22A0, 0x46A6,
        0x4CA6, 0x5461, 0xA650, 0xAA60, 0xA167, 0xAA5C, 0xA259, 0xAA60,
        0xA254, 0xA067, 0xA45C, 0xA634, 0x52AA, 0x58A8, 0x3415, 0x0DA2,
        0x63A0, 0x6AA6, 0x58A6, 0x6062, 0xA65C, 0xAA6C, 0xA189, 0xAA68,
        0xA27C, 0xAA6C, 0x22A0, 0x89A4, 0x68A6, 0x3653, 0xAA64, 0xA836,
        0x140D, 0x22A0, 0x8CA6, 0x64A6, 0x6C63, 0xA668, 0xAA78, 0xA1AC,
        0xAA74, 0xA29E, 0xAA78, 0x22A0, 0xACA4, 0x74A6, 0x3854, 0xAA70,
        0xA838, 0x150D, 0xA2A8, 0xA0AF, 0xA670, 0xA678, 0x64A6, 0x74AA,
        0x84A1, 0xCFAA, 0x80A2, 0xC1AA, 0x8422, 0xA0CF, 0xA480, 0xA63A,
        0x55AA, 0x7CA8, 0x3A15, 0x0DA2, 0xCBA0, 0xD2A6, 0x7CA6, 0x8465,
        0xA680, 0xAA90, 0xA1F2, 0xAA8C, 0xA2E4, 0xAA90, 0x22A0, 0xF2A4,
        0x8CA6, 0x3C56, 0xAA88, 0xA83C, 0x150D, 0xA2EE, 0xA000, 0xA688,
        0xA690, 0x66A6, 0x8C00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
    };

    eepromDump(data);
}

void MainWindow::eepromDump(std::vector<uint16_t> data)
{
    dumpParameters(data, ui->eepromTextEdit);
}

void MainWindow::dumpParameters(std::vector<uint16_t> data, QTextEdit *outputTextEdit)
{
    std::map<int, QString> bitRates;
    bitRates[0] = "Automatic 1200 - 19200 bps";
    bitRates[3] = "300 bps";
    bitRates[4] = "600 bps";
    bitRates[5] = "1200 bps";
    bitRates[6] = "2400 bps";
    bitRates[7] = "4800 bps";
    bitRates[8] = "9600 bps";
    bitRates[9] = "19200 bps";

    QString details;

    for (int i = 0; i < data.size(); ++i) {
        uint16_t entry = data[i];
        int bitRate = (entry >> 8) & 0xF;

        switch (i) {
        case 0x00:	// Parameter 00
            details += "00\tControl bits and bit rate\n\n";
            details += "\tBitrate: " + bitRates[bitRate] + "\n";
            details += QString::asprintf("\tNumber of permitted addresses: %d\n\n", entry & 0xF);
            break;

        case 0x01:	// Parameter 01
            details += "01\tAddress and control bits\n\n";
            details += QString::asprintf("\tFirst address of module: %d\n\n", (entry & 0xFF00) >> 8);
            break;

        case 0x02:	// Parameter 02
            details += "02\tCustomer options and PLC spy address\n\n";
            details += QString::asprintf("\t0x%04x\n\n", entry);
            break;

        case 0x03:	// Parameter 03
            details += "03\tTimeouts and debounce time\n\n";
            details += QString::asprintf("\t0x%04x\n\n", entry);
            break;

        case 0x04:	// Parameter 04
            details += "04\tInterlock mask I1 and I2\n\n";
            details += QString::asprintf("\tI1 0x%02x\n", (entry & 0xFF00) >> 4);
            details += QString::asprintf("\tI2 0x%02x\n\n", (entry & 0xFF));
            break;

        case 0x05:	// Parameter 05
            details += "05\tInterlock mask I3 and I4\n\n";
            details += QString::asprintf("\tI3 0x%02x\n", (entry & 0xFF00) >> 4);
            details += QString::asprintf("\tI4 0x%02x\n\n", (entry & 0xFF));
            break;

        case 0x06:	// Parameter 06
            details += "06\tInterlock mask I5 and I6\n\n";
            details += QString::asprintf("\tI5 0x%02x\n", (entry & 0xFF00) >> 4);
            details += QString::asprintf("\tI6 0x%02x\n\n", (entry & 0xFF));
            break;

        case 0x07:	// Parameter 07
            details += "07\tInterlock mask I7 and inhibit register\n\n";
            details += QString::asprintf("\tI7 0x%02x\n", (entry & 0xFF00) >> 4);
            details += QString::asprintf("\tInhibited outputs 0x%02x\n\n", (entry & 0xFF));
            break;

        case 0x08:	// Parameter 08
            details += "08\tOverload and output register\n\n";
            details += QString::asprintf("\tActive overloaded outputs 0x%02x\n", (entry & 0xFF00) >> 4);
            details += QString::asprintf("\tOutput register 0x%02x\n\n", (entry & 0xFF));
            break;

        case 0x09:	// Parameter 09
            details += "09\tInput register\n\n";
            details += QString::asprintf("\tDebounced inputs 0x%04x\n\n", entry);
            break;

        case 0x0A:	// Parameter 0A
            details += "0A\tEdge trigger control\n\n";
            details += QString::asprintf("\t0x%04x\n\n", entry);
            break;

        case 0x0B:	// Parameter 0B
            details += "0B\tGray code mask\n\n";
            details += QString::asprintf("\t0x%04x\n\n", entry);
            break;

        case 0x0C:	// Parameter 0C
            details += "0C\tInput inversion mask\n\n";
            details += QString::asprintf("\t0x%04x\n\n", entry);
            break;

        case 0x0D:	// Parameter 0D
            details += "0D\tBinary converted Gray code\n\n";
            details += QString::asprintf("\t0x%04x\n\n", entry);
            break;

        case 0x0E:	// Parameter 0E
            details += "0E\tInc. encoder X\n\n";
            details += QString::asprintf("\t0x%04x\n\n", entry);
            break;

        case 0x0F:	// Parameter 0F
            details += "0F\tInc. encoder Y\n\n";
            details += QString::asprintf("\t0x%04x\n\n", entry);
            break;

        case 0x10:	// Parameter 10
            details += "10\tInc. encoder Z\n\n";
            details += QString::asprintf("\t0x%04x\n\n", entry);
            break;

        case 0x11:	// Parameter 11
            details += "11\tPLC controlled outputs / program counter\n\n";
            details += QString::asprintf("\tPLC controlled outputs 0x%02x\n\n", (entry & 0xFF00) >> 4);
            details += QString::asprintf("\tPLC Program counter 0x%02x\n\n", (entry & 0xFF));
            break;

        case 0x12:	// Parameter 12
            details += "12\tPLC timebase and run flags\n\n";
            details += QString::asprintf("\tPLC timer tick size 0x%02x\n\n", (entry & 0xFF00) >> 4);
            details += QString::asprintf("\tEEPSH remapping of EEPROM active 0x%0x\n\n", (entry & 0x0040));
            details += QString::asprintf("\tPLC single step 0x%0x\n\n", (entry & 0x0010));
            details += QString::asprintf("\tSingle step done 0x%0x\n\n", (entry & 0x0020));
            details += QString::asprintf("\tPLC run bits 0x%0x\n\n", (entry & 0x0F));
            break;

        case 0x13:	// Parameter 13
            details += "13\tPLC status flags\n\n";
            details += QString::asprintf("\t0x%04x\n\n", entry);
            break;

        case 0x14:	// Parameter 14
            details += "14\tPLC 16 bit V accumulator\n\n";
            details += QString::asprintf("\t0x%04x\n\n", entry);
            break;

        case 0x15:	// Parameter 15
            details += "15\tPLC 16 bit timer\n\n";
            details += QString::asprintf("\t0x%04x\n\n", entry);
            break;

        case 0x16:	// Parameter 16
            details += "16\tRTC most significant word\n\n";
            details += QString::asprintf("\t0x%04x\n\n", entry);
            break;

        case 0x17:	// Parameter 17
            details += "17\tRTC least significant word\n\n";
            details += QString::asprintf("\t0x%04x\n\n", entry);
            break;

        case 0x18:	// Parameter 18
            details += "18\tCounter C8\n\n";
            details += QString::asprintf("\t0x%04x\n\n", entry);
            break;

        case 0x19:	// Parameter 19
            details += "19\tCounter C9\n\n";
            details += QString::asprintf("\t0x%04x\n\n", entry);
            break;

        case 0x1A:	// Parameter 1A
            details += "1A\tCounter C10\n\n";
            details += QString::asprintf("\t0x%04x\n\n", entry);
            break;

        case 0x1B:	// Parameter 1B
            details += "1B\tCounter C11\n\n";
            details += QString::asprintf("\t0x%04x\n\n", entry);
            break;

        case 0x1C:	// Parameter 1C
            details += "1C\tCounter C12\n\n";
            details += QString::asprintf("\t0x%04x\n\n", entry);
            break;

        case 0x1D:	// Parameter 1D
            details += "1D\tCounter C13\n\n";
            details += QString::asprintf("\t0x%04x\n\n", entry);
            break;

        case 0x1E:	// Parameter 1E
            details += "1E\tCounter C14 most significant word\n\n";
            details += QString::asprintf("\t0x%04x\n\n", entry);
            break;

        case 0x1F:	// Parameter 1F
            details += "1F\tCounter C14 least significant word\n\n";
            details += QString::asprintf("\t0x%04x\n\n", entry);
            break;

        default:
            details += QString::asprintf("0x%02x (%04x)\n", i, entry);
        }
    }

    outputTextEdit->append(details);
}

void MainWindow::dumpParametersAsHex(std::vector<uint16_t> data, QTextEdit *outputTextEdit)
{
    QString outputString;
    int startAddress = parseHexString(ui->startAddressTextBox->text());

    outputString.append(QString::asprintf("%04x\n", startAddress));

    for (int i = 0; i < data.size(); ++i) {
        outputString.append(QString::asprintf("%04x ", data[i]));
        if (((i + 1) % 8) == 0)
            outputString.append("\n");
    }

    outputTextEdit->append(outputString);
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

std::vector<int> MainWindow::parseHexStrings(QString input)
{
    if (input.length() == 0) return {};

    std::vector<int> result;
    QStringList list;

    list = input.split(QRegularExpression("\\s+"));

    for (int i = 0; i < list.length(); ++i) {
        int n = parseHexString(list[i]);
        if (n >= 0)
            result.push_back(n);
    }

    return result;
}

int MainWindow::parseHexString(QString input)
{
    if (input.length() == 0) return 0;

    int result;
    bool ok;

    result = (int) input.toUInt(&ok, 16);
    if (ok)
        return result;

    return -1;
}

void MainWindow::on_sendCommand_clicked()
{
    QString input = ui->commandTextbox->text();
    std::vector<int> command = parseHexStrings(input);

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
    std::vector<int> outputs = parseHexStrings(ui->outputTextBox->text());
    int output = outputs[0];
    int outputCount = 1;
    int bus = hw.bus;
    unsigned int stationAddress = ui->stationAddressTextBox->text().toInt();
    int silent;

    QString text = QString::asprintf("SioxData bus %d address %d output 0x%x", bus, stationAddress, output);
    log(text);
    SioxData(bus, stationAddress, output, outputCount, input, &silent);
    text = QString::asprintf("Input:\t%s\nInputCount:\t%d\nSilent:\t%d\nBusy:\t%d\n", input, silent);
    log(text);

    delete[] input;
}

/*
void MainWindow::on_testSioxTextEx_clicked()
{
    if (ui->outputTextBox->text().length() == 0) return;
    if (ui->groupAddressTextBox->text().length() == 0) return;
    if (ui->stationAddressTextBox->text().length() == 0) return;

    std::vector<int> outputs = parseHexStrings(ui->outputTextBox->text());
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
    log(text);

    delete[] output;
    delete[] input;
}
*/

void MainWindow::on_testSioxText_clicked()
{
    if (ui->outputTextBox->text().length() == 0) return;
    if (ui->stationAddressTextBox->text().length() == 0) return;

    std::vector<int> outputs = parseHexStrings(ui->outputTextBox->text());
    int outputCount = outputs.size();
    char *output = new char[outputCount + 1];
    char *input = new char[50];
    int inputCount;
    int bus = hw.bus;
    unsigned int stationAddress = ui->stationAddressTextBox->text().toInt();
    int numbered = 0;
    int silent;
    int busy;

    for (int i = 0; i < outputCount; ++i)
        output[i] = (char) outputs[i];
    output[outputCount] = '\0';

    QString text = QString::asprintf("SioxText bus %d groupAddress %d stationAddress %d output ", bus, stationAddress);

    for (int i = 0; i < outputCount; ++i)
        text += QString::asprintf("0x%x ", output[i]);

    log(text);
    SioxText(bus, stationAddress, output, outputCount, input, &inputCount, numbered, &silent, &busy);
    text = QString::asprintf("Input:\t%s\nInputCount:\t%d\nSilent:\t%d\nBusy:\t%d\n", input, inputCount, silent, busy);
    log(text);

    delete[] output;
    delete[] input;
}

void MainWindow::on_testRAMWrite_clicked()
{
    if (ui->stationAddressTextBox->text().length() == 0) return;

    int bus = hw.bus;
    unsigned int stationAddress = ui->stationAddressTextBox->text().toInt();
    int silent;
    char enquiry[300];
    unsigned int parameterNr { 0x08 };
    int parameter { 0 };
    int mask = parseHexString(ui->outputTextBox->text());

    SioxEnquiry(bus, stationAddress, (char *) &enquiry, &silent);
    if (!silent)
        log(QString::asprintf("Result of enquiry: %s", enquiry));

    SioxRamRead(bus, stationAddress, parameterNr, &parameter, &silent);

    log(QString::asprintf("Result of RAM read of parameter 0x%02x: 0x%04x (silent %d)", parameterNr, parameter, silent));

    parameter = (parameter & 0xFF00) | mask;

    log(QString::asprintf("Writing 0x%04x to parameter 0x%02x", parameter, parameterNr));
    SioxRamWrite(bus, stationAddress, parameterNr, parameter, &silent);

}

void MainWindow::on_readRAMButton_clicked()
{
    int startAddress = parseHexString(ui->startAddressTextBox->text());
    int lastAddress = parseHexString(ui->lastAddressTextBox->text());
    bool outputHex = ui->showHexCheckBox->isChecked();

    readData(startAddress, lastAddress, ui->ramOutputTextEdit, true, outputHex);
}

void MainWindow::readData(int startAddress, int lastAddress, QTextEdit *outputTextEdit, bool readRam, bool outputHex)
{
    QLCDNumber* lcd = ui->addressLCD;
    int bus = hw.bus;
    int stationAddress = ui->stationAddressTextBox->text().toInt();
    std::vector<uint16_t> parameters;
    int parameter;
    int silent;

    for (int address = startAddress; address <= lastAddress; ++address) {
        lcd->display(address);

        if (readRam)
            SioxRamRead(bus, stationAddress, address, &parameter, &silent);
        else
            SioxEepromRead(bus, stationAddress, address, &parameter, &silent);

        parameter = silent ? 0xDEAD : parameter;
        parameters.push_back(parameter);
    }

    if (outputHex)
        dumpParametersAsHex(parameters, outputTextEdit);
    else
        dumpParameters(parameters, outputTextEdit);

}

void MainWindow::on_testRAMStuffButton_clicked()
{
    QTextEdit *output = ui->ramOutputTextEdit;
    int outputPortsParameter = 8;
    int bus = hw.bus;
    int stationAddress = ui->stationAddressTextBox->text().toInt();
    int parameterValue;
    int silent;
    int busy;
    int numbered = true;
    int responseLength;
    int responseSize { 1000 };
    char *s = new char[100];
    char *response = new char[responseSize];

    for (int i = 0; i < responseSize; ++i) response[i] = 0;

    strcpy(s, "SXWIN32");
    SioxText(bus, stationAddress, s, -1, response, &responseLength, numbered, &silent, &busy);

    output->append(QString::asprintf("Silent %d\n", silent));
    output->append(QString::asprintf("Busy %d\n", busy));
    output->append(QString::asprintf("Response length %d\n", responseLength));
    output->append(QString::asprintf("Response: %s\n", response));

    for (int i = 0; i < responseSize; ++i) response[i] = 0;

    SioxRamRead(bus, stationAddress, outputPortsParameter, &parameterValue, &silent);
    output->append(QString::asprintf("Read value 0x%04x  %d\n", parameterValue, silent));
    parameterValue = 3;
    SioxMemoryWrite(bus, stationAddress, outputPortsParameter, parameterValue, &silent);
    if (silent == 0)
            GetString(bus, response, responseSize, 100);
    output->append(QString::asprintf("Wrote value 0x%04x\n", parameterValue));

    if (strlen(response) > 0)
        output->append(QString::asprintf("Got response: %s\n", response));

    for (int i = 0; i < 5; ++i) {
        SioxRamRead(bus, stationAddress, outputPortsParameter, &parameterValue, &silent);
        output->append(QString::asprintf("Read value 0x%04x  %d\n", parameterValue, silent));
        Sleep(1);
    }

    delete[] response;
    delete[] s;

    unsigned int groupAddress = ui->groupAddressTextBox->text().toInt();
    int bitNumber = 3;

    output->append(QString::asprintf("Flipping bit %d on parameter %d\n", bitNumber, outputPortsParameter));
    SioxRamBitEx(bus, groupAddress, stationAddress, outputPortsParameter, bitNumber, 1, &silent);
    output->append(QString::asprintf("Silent %d\n", silent));
    SioxRamRead(bus, stationAddress, outputPortsParameter, &parameterValue, &silent);
    output->append(QString::asprintf("Read value 0x%04x  %d\n", parameterValue, silent));
}

void MainWindow::on_writeValueButton_clicked()
{
    int startAddress = parseHexString(ui->startAddressTextBox->text());
    int lastAddress = parseHexString(ui->lastAddressTextBox->text());
    int newValue = parseHexString(ui->valueTextBox->text());
    QLCDNumber* lcd = ui->addressLCD;
    int bus = hw.bus;
    int stationAddress = ui->stationAddressTextBox->text().toInt();
    int silent;

    ui->ramOutputTextEdit->append("\n\nBefore write:\n");
    readData(startAddress, lastAddress, ui->ramOutputTextEdit, true, true);

    for (int address = startAddress; address <= lastAddress; ++address) {
        lcd->display(address);
        SioxMemoryWrite(bus, stationAddress, address, newValue, &silent);
    }

    ui->ramOutputTextEdit->append("\n\nAfter write:\n\tEEPROM:\n");
    readData(startAddress, lastAddress, ui->ramOutputTextEdit, false, true);

    ui->ramOutputTextEdit->append("\nRAM:\n");
    readData(startAddress, lastAddress, ui->ramOutputTextEdit, true, true);
}

void MainWindow::on_setBitButton_clicked()
{
    QTextEdit *output = ui->ramOutputTextEdit;
    int outputPortsParameter = 8;
    int bitNumber = ui->bitTextBox->text().toInt();
    int state = ui->bitStateTextBox->text().toInt();

    output->append(QString::asprintf("Setting bit %d on parameter %d to %d\n", bitNumber, outputPortsParameter, state));
    setPortState(bitNumber, state);
}

void MainWindow::activatePort(int portNumber)
{
    setPortState(portNumber, 1);
}

void MainWindow::deactivatePort(int portNumber)
{
    setPortState(portNumber, 0);
}

void MainWindow::setPortState(int portNumber, int state)
{
    int stationAddress = ui->stationAddressTextBox->text().toInt();
    int groupAddress = ui->groupAddressTextBox->text().toInt();
    int bus = hw.bus;
    int outputPortsParameter = 8;
    int silent;

    SioxRamBitEx(bus, groupAddress, stationAddress, outputPortsParameter, portNumber, state, &silent);
}







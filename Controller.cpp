#include "Controller.h"
#include <QString>
#include <vector>
#include <windows.h>

Controller::Controller()
{
	bus = 0;
}

Controller::~Controller()
{
	if (bus >= 0)
		ExitSioxBus(bus);
}

bool Controller::init(QString port, int speed)
{
    bus = InitSioxBus((char*)port.toStdString().c_str(), speed);

	return (bus >= 0);
}

std::vector<int> Controller::send(std::vector<int> message)
{
	if (bus < 0) {
		return { 0 };
	}

	std::vector<int> response;

    for (char ch : message)
        SendChar(bus, ch);

    while (!CharReceived(bus))
        Sleep(1);

    while (CharReceived(bus))
        response.push_back(GetChar(bus, 0));

	return response;
}

QString Controller::getErrorMessage()
{
	const int SIZE{ 120 };
	char message[SIZE];		// Needs to have space for at least 80 chars according to documentation

	InitSioxBusErrorMsg(bus, message);

	return QString(message);
}

QString Controller::result()
{
	std::vector<QString> errorMessages {
		"",
		"The module is not responding (silent)",
		"The SIOX bus can not be accessed (e.g. network error)",
		"Invalid bus handle",
		"Function not supported in this mode",
		"Bus short circuit",
		"Communication error",
		"Possibly double addressed modules"
	};

	QString result;
	int errorCode;

	errorCode = SioxResult(bus);

	if ((errorCode > 0) && (errorCode < 8))
		result = "Error: " + errorMessages[errorCode];
	else
		result = QString::asprintf("Result: %d", errorCode);

	return result;
}


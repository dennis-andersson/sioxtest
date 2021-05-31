#pragma once

#include <Siox30.h>
#include <QString>
#include <string>
#include <vector>

class Controller
{
	int portTable[12]{ 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23, 24 };

public:
    int bus{ 0 };

    Controller();
	~Controller();

    bool init(QString port, int speed);

	QString getErrorMessage();
	QString result();

	std::vector<int> activate(int port);
	std::vector<int> deactivate(int port);
	std::vector<int> activateBoth();
	std::vector<int> deactivateBoth();
	std::vector<int> showTargets();
	std::vector<int> hideTargets();
	std::vector<int> send(std::vector<int> message);
	void log(bool sent, std::vector<int> message);
	void log(QString message);

	void test();	// Test hardware function
};


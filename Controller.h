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
    std::vector<int> send(std::vector<int> message);
	QString getErrorMessage();
	QString result();
};


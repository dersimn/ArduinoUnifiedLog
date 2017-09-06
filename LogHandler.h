#ifndef LogHandler_h
#define LogHandler_h

#include <Arduino.h>
#include "LogModule.h"

#define MAX_MODULES 10

class LogHandler {
private:
	int count = 0;
	LogModule* modules[MAX_MODULES];
public:
	bool addModule(LogModule* module);
	void write_message(int logLevel, String message);
};

#endif

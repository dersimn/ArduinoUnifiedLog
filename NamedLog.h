#ifndef NamedLog_h
#define NamedLog_h

#include <Arduino.h>
#include "LogModule.h"
#include "LogHandler.h"
#include "GenericLog.h"

class NamedLog : public GenericLog {
private:
	const String logName;
public:
	NamedLog(LogHandler& handler, String name);

	void level(int logLevel, String message);
};

#endif

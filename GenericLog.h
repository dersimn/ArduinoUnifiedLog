#ifndef GenericLog_h
#define GenericLog_h

#include <Arduino.h>
#include "LogModule.h"
#include "LogHandler.h"

class GenericLog {
protected:
	LogHandler& logHandler;
public:
	GenericLog(LogHandler& handler);

	virtual void level(int logLevel, const String& message);

    void debug(const String& message);
	void info(const String& message);
	void warn(const String& message);
	void error(const String& message);

	void operator()(int logLevel, const String& message);
	void operator()(const String& message);
};

#endif

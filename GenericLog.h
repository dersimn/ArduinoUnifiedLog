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

	virtual void level(int logLevel, String message);

    void debug(String message);
	void info(String message);
	void warn(String message);
	void error(String message);

	void operator()(int logLevel, String message);
	void operator()(String message);
};

#endif

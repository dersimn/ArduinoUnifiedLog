#include "NamedLog.h"

NamedLog::NamedLog(LogHandler& handler, String name): GenericLog(handler),logName(name) { }

void NamedLog::level(int logLevel, String message) {
	String prefix = String("[");
	prefix += millis();
	prefix += "][";
	prefix += logName;
	prefix += "] ";

	logHandler.write_message(logLevel, prefix + message);
}
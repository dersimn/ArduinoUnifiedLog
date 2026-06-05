#include "NamedLog.h"

NamedLog::NamedLog(LogHandler& handler, String name): GenericLog(handler),logName(name) { }

void NamedLog::level(int logLevel, const String& message) {
	String out;
	out.reserve(message.length() + logName.length() + 16);
	out += "[";
	out += millis();
	out += "][";
	out += logName;
	out += "] ";
	out += message;

	logHandler.write_message(logLevel, out);
}
#include "GenericLog.h"

GenericLog::GenericLog(LogHandler& handler) : logHandler(handler) { }

void GenericLog::level(int logLevel, const String& message) {
	String out;
	out.reserve(message.length() + 16);
	out += "[";
	out += millis();
	out += "] ";
	out += message;

	logHandler.write_message(logLevel, out);
}

void GenericLog::debug(const String& message) {
	level(0, message);
}
void GenericLog::info(const String& message) {
	level(10, message);
}
void GenericLog::warn(const String& message) {
	level(20, message);
}
void GenericLog::error(const String& message) {
	level(30, message);
}

void GenericLog::operator()(int logLevel, const String& message) {
	level(logLevel, message);
}
void GenericLog::operator()(const String& message) {
	level(10, message);
}
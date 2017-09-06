#include "GenericLog.h"

GenericLog::GenericLog(LogHandler& handler) {
	setLogHandler(handler);
}
void GenericLog::setLogHandler(LogHandler& handler) {
	(*this).logHandler = &handler;
}

void GenericLog::level(int logLevel, String message) {
	String prefix = String("[");
	prefix += millis();
	prefix += "] ";

	(*logHandler).write_message(logLevel, prefix + message);
}

void GenericLog::info(String message) {
	level(1, message);
}
void GenericLog::warn(String message) {
	level(2, message);
}
void GenericLog::error(String message) {
	level(3, message);
}

void GenericLog::operator()(int logLevel, String message) {
	level(logLevel, message);
}
void GenericLog::operator()(String message) {
	level(0, message);
}
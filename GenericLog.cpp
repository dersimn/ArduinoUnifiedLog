#include "GenericLog.h"

GenericLog::GenericLog(LogHandler& handler) : logHandler(handler) { }

void GenericLog::level(int logLevel, String message) {
	String prefix = String("[");
	prefix += millis();
	prefix += "] ";

	logHandler.write_message(logLevel, prefix + message);
}

void GenericLog::debug(String message) {
	level(0, message);
}
void GenericLog::info(String message) {
	level(10, message);
}
void GenericLog::warn(String message) {
	level(20, message);
}
void GenericLog::error(String message) {
	level(30, message);
}

void GenericLog::operator()(int logLevel, String message) {
	level(logLevel, message);
}
void GenericLog::operator()(String message) {
	level(10, message);
}
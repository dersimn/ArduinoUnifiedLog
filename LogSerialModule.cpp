#include "LogSerialModule.h"

LogSerialModule::LogSerialModule(int baud) {
	Serial.begin(baud);
}

void LogSerialModule::write_message(String message) {
	Serial.println(message);
}
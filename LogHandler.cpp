#include "LogHandler.h"

bool LogHandler::addModule(LogModule* module) {
	if ( count < MAX_MODULES ) {
		modules[count++] = module;
		return true;
	} else {
		return false;
	}
}

void LogHandler::write_message(int logLevel, String message) {
	for (int i = 0 ; i < count ; i++) {
		if ( logLevel >= (*modules[i]).getMinimumLogLevel() ) {
			(*modules[i]).write_message(message);
		}
	}
}
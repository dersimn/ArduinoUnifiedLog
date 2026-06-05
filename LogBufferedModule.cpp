#include "LogBufferedModule.h"

void LogBufferedModule::write_message(const String& message) {
	if (isConnected()) {
		flushCache();
		if (!send(message)) {
			bufferMessage(message);
		}
	} else {
		bufferMessage(message);
	}
}

void LogBufferedModule::bufferMessage(const String& message) {
	cache += message;
	cache += "\n";

	// Enforce the cap by discarding the oldest messages (lines) first.
	while (cache.length() > maxCacheSize) {
		int nl = cache.indexOf('\n');
		if (nl < 0) {
			// A single message longer than the cap: keep its tail.
			cache = cache.substring(cache.length() - maxCacheSize);
			break;
		}
		cache = cache.substring(nl + 1);
	}
}

void LogBufferedModule::flushCache() {
	if (cache.length() == 0) {
		return;
	}

	// Replay cached messages oldest first. If a send fails, keep the unsent
	// remainder cached so nothing is lost.
	int start = 0;
	while (start < (int)cache.length()) {
		int nl = cache.indexOf('\n', start);
		if (nl < 0) {
			nl = cache.length();
		}

		String line = cache.substring(start, nl);
		if (line.length() && !send(line)) {
			cache = cache.substring(start);
			return;
		}

		start = nl + 1;
	}

	cache = "";
}

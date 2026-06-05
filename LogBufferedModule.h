#ifndef LogBufferedModule_h
#define LogBufferedModule_h

#include <Arduino.h>
#include "LogModule.h"

// Maximum number of bytes to cache while disconnected. Define this before
// including the module (e.g. via PlatformIO build_flags: -DLOG_CACHE_MAX_SIZE=4096)
// to change the default. It can also be overridden at runtime per module via
// setMaxCacheSize().
#ifndef LOG_CACHE_MAX_SIZE
#define LOG_CACHE_MAX_SIZE 2048
#endif

// Base class for modules whose transport can be temporarily unavailable
// (network down, broker disconnected, ...). Messages are cached while offline
// and replayed, oldest first, once the transport recovers. The cache is capped
// at maxCacheSize bytes; when full the oldest cached messages are dropped.
//
// Concrete modules only need to implement isConnected() and send().
class LogBufferedModule : public LogModule {
public:
	void   setMaxCacheSize(size_t bytes) { maxCacheSize = bytes; }
	size_t getMaxCacheSize() { return maxCacheSize; }

	virtual void write_message(const String& message) override;
protected:
	// Return true when the transport is ready to send.
	virtual bool isConnected() = 0;
	// Send a single message. Return true on success; on false the message is
	// (re)cached for a later attempt.
	virtual bool send(const String& message) = 0;

	void bufferMessage(const String& message);
	void flushCache();

	String cache;
	size_t maxCacheSize = LOG_CACHE_MAX_SIZE;
};

#endif

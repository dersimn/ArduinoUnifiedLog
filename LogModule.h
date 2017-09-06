#ifndef LogModule_h
#define LogModule_h

#include <Arduino.h>


class LogModule {
private:
	int outputMinimumLogLevel = 0;
public:
	int  getMinimumLogLevel() { return outputMinimumLogLevel; }
	void setMinimumLogLevel(int min) { outputMinimumLogLevel = min; }

	virtual void write_message(String message); 
};

#endif

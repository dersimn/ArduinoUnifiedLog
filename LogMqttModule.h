#ifndef LogMqttModule_h
#define LogMqttModule_h

#include <Arduino.h>

#include "LogBufferedModule.h"
#include <PubSubClient.h>
#include <PubSubClientTools.h>

class LogMqttModule : public LogBufferedModule {
public:
	LogMqttModule(PubSubClientTools& mqtt, String topic);

protected:
	virtual bool isConnected();
	virtual bool send(String message);

	PubSubClientTools& mqtt;
	String topic;
};

#endif

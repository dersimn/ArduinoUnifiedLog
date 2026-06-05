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
	virtual bool isConnected() override;
	virtual bool send(const String& message) override;

	PubSubClientTools& mqtt;
	String topic;
};

#endif

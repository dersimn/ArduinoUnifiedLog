#ifndef LogMqttModule_h
#define LogMqttModule_h

#include <Arduino.h>

#include "LogModule.h"
#include <PubSubClient.h>
#include <PubSubClientTools.h>

class LogMqttModule : public LogModule {
public:
	LogMqttModule(PubSubClientTools& mqtt, String topic);

	virtual void write_message(String message);
protected:
	PubSubClientTools& mqtt;
    String topic;
    String messageStash;
};

#endif

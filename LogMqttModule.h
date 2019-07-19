#ifndef LogMqttModule_h
#define LogMqttModule_h

#include <Arduino.h>

#include "LogModule.h"
#include <PubSubClient.h>

class LogMqttModule : public LogModule {
public:
	LogMqttModule(PubSubClient& mqtt, String topic);

	virtual void write_message(String message);
protected:
	PubSubClient& mqtt;
	char _topic[MQTT_MAX_PACKET_SIZE];
	char _msg[MQTT_MAX_PACKET_SIZE];
};

#endif

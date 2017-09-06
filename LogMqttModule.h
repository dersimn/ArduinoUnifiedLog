#ifndef LogMqttModule_h
#define LogMqttModule_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
	#include <WProgram.h>
#endif

#include "LogModule.h"
#include <PubSubClient.h>

#define MQTT_SIZE 1024

class LogMqttModule : public LogModule {
public:
	LogMqttModule(PubSubClient* mqtt, String topic);

	virtual void write_message(String message);
protected:
	PubSubClient* _mqtt;
	char _topic[MQTT_SIZE];
	char _msg[MQTT_SIZE];
};

#endif

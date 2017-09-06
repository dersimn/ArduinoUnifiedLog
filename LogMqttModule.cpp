#include "LogMqttModule.h"

LogMqttModule::LogMqttModule(PubSubClient* mqtt, String topic) {
	_mqtt = mqtt;
	topic.toCharArray(_topic, MQTT_SIZE);
}

void LogMqttModule::write_message(String message) {
	if ( (*_mqtt).connected() ) {
		message.toCharArray(_msg, MQTT_SIZE);

		(*_mqtt).publish(_topic, _msg);
	}
}
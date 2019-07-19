#include "LogMqttModule.h"

LogMqttModule::LogMqttModule(PubSubClient& _mqtt, String topic) : mqtt(_mqtt) {
	topic.toCharArray(_topic, MQTT_MAX_PACKET_SIZE);
}

void LogMqttModule::write_message(String message) {
	if ( mqtt.connected() ) {
		message.toCharArray(_msg, MQTT_MAX_PACKET_SIZE);

		mqtt.publish(_topic, _msg);
	}
}
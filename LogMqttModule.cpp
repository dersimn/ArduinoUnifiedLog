#include "LogMqttModule.h"

LogMqttModule::LogMqttModule(PubSubClientTools& _mqtt, String _topic) : mqtt(_mqtt), topic(_topic) {
    setMinimumLogLevel(10);
}

bool LogMqttModule::isConnected() {
	return mqtt.connected();
}

bool LogMqttModule::send(const String& message) {
	return mqtt.publish(topic, message);
}

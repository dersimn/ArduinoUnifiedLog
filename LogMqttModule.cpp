#include "LogMqttModule.h"

LogMqttModule::LogMqttModule(PubSubClientTools& _mqtt, String _topic) : mqtt(_mqtt), topic(_topic) {
    setMinimumLogLevel(10);
}

void LogMqttModule::write_message(String message) {
	if (mqtt.connected()) {
		mqtt.publish(topic, messageStash+message);
        messageStash = "";
	} else {
        messageStash += message;
        messageStash += "\n";
    }
}
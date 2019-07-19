#include <ESP8266WiFi.h>

#include <PubSubClient.h>         // https://github.com/knolleary/pubsubclient
#include <PubSubClientTools.h>    // https://github.com/dersimn/ArduinoPubSubClientTools

#include <GenericLog.h>
#include <NamedLog.h>
#include <LogHandler.h>
#include <LogModule.h>
#include <LogSerialModule.h>
#include <LogMqttModule.h>

#define WIFI_SSID         "..."
#define WIFI_PASS         "..."
#define MQTT_SERVER       "10.1.1.100"

WiFiClient espClient;
PubSubClient client(MQTT_SERVER, 1883, espClient);
PubSubClientTools mqtt(client);

LogHandler logHandler;
LogSerialModule serialModule(115200);
LogMqttModule mqttModule(mqtt, "esplogtest/esp0");

GenericLog Log    (logHandler);
NamedLog   LogWiFi(logHandler, "WiFi");
NamedLog   LogMqtt(logHandler, "Mqtt");

long lastMsg = 0;
int value = 0;

void setup() {
  logHandler.addModule(&serialModule);
  logHandler.addModule(&mqttModule);
  
  Log.info("Running Setup..");
  
  LogWiFi.info(String("Connecting to ")+WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
}

void loop() {
  client.loop();
  
  long now = millis();
  if (now - lastMsg > 2000) {
    if (WiFi.status() == WL_CONNECTED) {
      LogWiFi.info(String("Connected to SSID: ") + WiFi.SSID() );
    }
    if (!client.connected()) {
      reconnect();
    }
    
    lastMsg = now;
    ++value;
    Log.info("testloop");
  }
}

void reconnect() {
  LogMqtt.info("Attempting MQTT connection...");
  if (client.connect("ESP8266Client")) {
    LogMqtt.info("connected");
  } else {
    LogMqtt.error(String("failed, rc=")+client.state()+String(" try again in 5 seconds"));
  }
}

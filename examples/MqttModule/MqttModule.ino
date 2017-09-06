#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <GenericLog.h>
#include <NamedLog.h>
#include <LogHandler.h>
#include <LogModule.h>
#include <LogSerialModule.h>
#include <LogMqttModule.h>

WiFiClient espClient;
PubSubClient client(espClient);

LogHandler logHandler;
LogSerialModule serialModule(115200);
LogMqttModule mqttModule(&client, "esplogtest/esp0");

GenericLog Log    (logHandler);
NamedLog   LogWiFi(logHandler, "WiFi");
NamedLog   LogMqtt(logHandler, "Mqtt");

#define ssid          "..."
#define password      "..."
#define mqtt_server   "10.0.0.111"

long lastMsg = 0;
int value = 0;

void setup() {
  logHandler.addModule(&serialModule);
  logHandler.addModule(&mqttModule);
  
  Log.info("Running Setup..");

  client.setServer(mqtt_server, 1883);
  
  LogWiFi.info(String("Connecting to ")+ssid);
  WiFi.begin(ssid, password);
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

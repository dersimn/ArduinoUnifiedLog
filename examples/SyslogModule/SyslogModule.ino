#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <GenericLog.h>
#include <NamedLog.h>
#include <LogHandler.h>
#include <LogModule.h>
#include <LogSerialModule.h>
#include <LogSyslogModule.h>

#define WIFI_SSID         "..."
#define WIFI_PASS         "..."
#define SYSLOG_SERVER     "10.1.1.100"
#define SYSLOG_PORT       514

#define APP_NAME "MyProject"
String chipId();                 // defined below; used during static init

const String s = "";
const String ESP_ID = chipId();
const String BOARD_ID = s+APP_NAME+"_"+ESP_ID;

WiFiUDP udp;

LogHandler logHandler;
LogSerialModule serialModule(115200);
LogSyslogModule syslogModule(udp, SYSLOG_SERVER, BOARD_ID, APP_NAME, SYSLOG_PORT);

GenericLog Log    (logHandler);
NamedLog   LogWiFi(logHandler, "WiFi");

long lastMsg = 0;

void setup() {
  logHandler.addModule(&serialModule);
  logHandler.addModule(&syslogModule);

  // Optionally tune how messages appear on the syslog server:
  // syslogModule.setFacility(SYSLOG_FAC_LOCAL0);
  // syslogModule.setSeverity(SYSLOG_SEV_INFO);

  Log.info("Running Setup..");

  LogWiFi.info(s+"Connecting to "+WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.setHostname(BOARD_ID.c_str());
  WiFi.setAutoReconnect(true);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
}

void loop() {
  long now = millis();
  if (now - lastMsg > 2000) {
    if (WiFi.status() == WL_CONNECTED) {
      LogWiFi.info(s+"Connected to SSID: "+WiFi.SSID());
    }

    lastMsg = now;
    Log.info("testloop");
  }
}

// Unique-ish device id from the lower 3 bytes of the eFuse MAC.
String chipId() {
  char buf[7];
  snprintf(buf, sizeof(buf), "%06X", (uint32_t)(ESP.getEfuseMac() & 0xFFFFFF));
  return String(buf);
}

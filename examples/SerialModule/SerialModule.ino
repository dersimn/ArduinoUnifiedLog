#include <GenericLog.h>
#include <NamedLog.h>
#include <LogHandler.h>
#include <LogModule.h>
#include <LogSerialModule.h>

LogHandler logHandler;
LogSerialModule serialModule(115200);

GenericLog Log    (logHandler);
NamedLog   LogWiFi(logHandler, "WiFi");
NamedLog   LogEgg (logHandler, "EggSample");

void setup() {
  logHandler.addModule(&serialModule);
  Log.info("Setup done");
}

void loop() {
  static int logLevel = 0;
  serialModule.setMinimumLogLevel( logLevel++ );
  
  Log.info("Test Info");
  Log.warn("Test Warn");
  Log.error("Test Error");
  Log.level(100, "Test Level (100)");
  Log("Same as Log.level");
  Log(100, "Same as Log.level(100, ...)");

  LogWiFi("Special Label Log");
  LogEgg("Another Label");

  delay(1000);
}

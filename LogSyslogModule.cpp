#include "LogSyslogModule.h"

LogSyslogModule::LogSyslogModule(UDP& _udp, String _server, String _hostname, String _appName, uint16_t _port) : udp(_udp), server(_server), hostname(_hostname), appName(_appName), port(_port) {
	setMinimumLogLevel(10);
}

void LogSyslogModule::write_message(String message) {
	// RFC 5424 header:
	// <PRI>VERSION TIMESTAMP HOSTNAME APP-NAME PROCID MSGID MSG
	// NILVALUE "-" is used for fields we cannot provide (no RTC for timestamp).
	int pri = facility * 8 + severity;

	String packet = String("<") + pri + ">1 - ";
	packet += (hostname.length() ? hostname : String("-"));
	packet += " ";
	packet += (appName.length() ? appName : String("-"));
	packet += " - - ";
	packet += message;

	if (udp.beginPacket(server.c_str(), port)) {
		udp.write((const uint8_t*)packet.c_str(), packet.length());
		udp.endPacket();
	}
}

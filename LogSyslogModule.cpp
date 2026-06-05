#include "LogSyslogModule.h"

LogSyslogModule::LogSyslogModule(UDP& _udp, String _server, String _hostname, String _appName, uint16_t _port) : udp(_udp), server(_server), hostname(_hostname), appName(_appName), port(_port) {
	setMinimumLogLevel(10);
}

bool LogSyslogModule::isConnected() {
	// UDP is connectionless; send() reports whether the datagram could be
	// dispatched, so always attempt and let it decide.
	return true;
}

bool LogSyslogModule::send(const String& message) {
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

	if (!udp.beginPacket(server.c_str(), port)) {
		return false;
	}
	udp.write((const uint8_t*)packet.c_str(), packet.length());
	return udp.endPacket() == 1;
}

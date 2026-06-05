#ifndef LogSyslogModule_h
#define LogSyslogModule_h

#include <Arduino.h>
#include <Udp.h>

#include "LogBufferedModule.h"

// Syslog severities (RFC 5424, section 6.2.1)
#define SYSLOG_SEV_EMERGENCY 0
#define SYSLOG_SEV_ALERT     1
#define SYSLOG_SEV_CRITICAL  2
#define SYSLOG_SEV_ERROR     3
#define SYSLOG_SEV_WARNING   4
#define SYSLOG_SEV_NOTICE    5
#define SYSLOG_SEV_INFO      6
#define SYSLOG_SEV_DEBUG     7

// Syslog facilities (RFC 5424, section 6.2.1)
#define SYSLOG_FAC_USER  1
#define SYSLOG_FAC_LOCAL0 16
#define SYSLOG_FAC_LOCAL1 17
#define SYSLOG_FAC_LOCAL2 18
#define SYSLOG_FAC_LOCAL3 19
#define SYSLOG_FAC_LOCAL4 20
#define SYSLOG_FAC_LOCAL5 21
#define SYSLOG_FAC_LOCAL6 22
#define SYSLOG_FAC_LOCAL7 23

class LogSyslogModule : public LogBufferedModule {
public:
	LogSyslogModule(UDP& udp, String server, String hostname, String appName, uint16_t port = 514);

	void setFacility(int facility) { this->facility = facility; }
	void setSeverity(int severity) { this->severity = severity; }

protected:
	virtual bool isConnected() override;
	virtual bool send(const String& message) override;

	UDP& udp;
	String server;
	String hostname;
	String appName;
	uint16_t port;

	int facility = SYSLOG_FAC_USER;
	int severity = SYSLOG_SEV_INFO;
};

#endif

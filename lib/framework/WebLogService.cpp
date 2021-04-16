
#include "WebLogService.h"

WebLogService::PrintLog::PrintLog() {
}

void WebLogService::PrintLog::onLog(LogHandler handler) {
  // set fields
  _logHandler = handler;
}

size_t WebLogService::PrintLog::write(const uint8_t* p, size_t n) {
  for (size_t i = 0; i < n; i++) {
    uint8_t c = p[i];
    if (c == 0)
      return i;
    write(c);
  }
  return n;
}

size_t WebLogService::PrintLog::write(uint8_t c) {
  if (c == 0)
    return 0;
  _logHandler(static_cast<char>(c));
  return 1;
}

WebLogService::WebLogService(AsyncWebServer* server, const String& url) {
  // set fields
  _eventSource = AsyncEventSource(url);

  // register in webserver
  server->addHandler(&_eventSource);

  // log
  _printLog.onLog([&](const char data) {
    if (data == *CR) {
      _eventSource.send(_data.c_str());
      _data = "";
    } else
      _data += data;
  });

  // set welcome message
  _eventSource.onConnect([](AsyncEventSourceClient* client) { client->send("connected", NULL, millis(), 1000); });
}

void WebLogService::begin(Print* parentOutput) {
  if (parentOutput != NULL) {
    static StreamUtils::LoggingPrint parentPrintLog = StreamUtils::LoggingPrint(*parentOutput, _printLog);
    output = &parentPrintLog;
  }

  Log.trace(F("Started web log @ (%s)" CR), _eventSource.url());
}

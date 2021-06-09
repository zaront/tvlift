/*
enables logging to an EventSource
*/

#ifndef WebLog_h
#define WebLog_h

#include <Arduino.h>
#include <ArduinoLog.h>
#include <StreamUtils.h>
#include <ESPAsyncWebServer.h>

typedef std::function<void(const char data)> LogHandler;

class WebLogService {
 public:
  class PrintLog : public Print {
    LogHandler _logHandler;

   public:
    PrintLog();
    void onLog(LogHandler handler);
    size_t write(const uint8_t* p, size_t n) override;
    size_t write(uint8_t c) override;
  };

 private:
  String _data = "";
  AsyncEventSource _eventSource = AsyncEventSource("");
  PrintLog _printLog = PrintLog();
  StreamUtils::LoggingPrint _parentPrintLog = StreamUtils::LoggingPrint(_printLog, _printLog);

 public:
  WebLogService(AsyncWebServer* server, const String& url = "/rest/log");
  Print* output = &_printLog;
  void begin(Print* parentOutput = &Serial);
};

#endif
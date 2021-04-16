#include <ESP8266React.h>
#include <WebLogService.h>
#include <LightStateService.h>
#include <MotorStateService.h>
#include <ButtonStateService.h>
#include <Arduino.h>

#define SERIAL_BAUD_RATE 115200

AsyncWebServer server(80);
ESP8266React esp8266React(&server);
WebLogService webLogService(&server);
LightStateService lightStateService = LightStateService(&server, esp8266React.getSecurityManager());
MotorStateService motorStateService = MotorStateService(&server, esp8266React.getSecurityManager());
ButtonStateService buttonStateService = ButtonStateService(&server, esp8266React.getSecurityManager());

void setup() {
  // start logging system - log to serial + webLog
  Serial.begin(SERIAL_BAUD_RATE);
  webLogService.begin(&Serial);
  Log.begin(LOG_LEVEL_VERBOSE, webLogService.output);

  // start the framework and demo project
  esp8266React.begin();

  // load the initial light settings
  lightStateService.begin();

  motorStateService.begin();

  buttonStateService.begin();

  // start the server
  server.begin();
}

void loop() {
  esp8266React.loop();
  buttonStateService.loop();
}

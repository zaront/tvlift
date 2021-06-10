#include <ESP8266React.h>
#include <WebLogService.h>
#include <LightStateService.h>
#include <MotorStateService.h>
#include <ButtonStateService.h>
#include <LiftCommandService.h>
#include <LiftSettingsService.h>
#include <LiftStatusService.h>
#include <Arduino.h>

#define SERIAL_BAUD_RATE 115200

AsyncWebServer server(80);
ESP8266React esp8266React(&server);
WebLogService webLogService(&server);
LiftCommandService liftCommandService = LiftCommandService(&server, esp8266React.getSecurityManager());
LiftSettingsService liftSettingsService = LiftSettingsService(&server, esp8266React.getFS(), esp8266React.getSecurityManager());
LiftStatusService liftStatusService = LiftStatusService(&server, esp8266React.getSecurityManager());

void setup() {
  // start logging system - log to serial + webLog
  Serial.begin(SERIAL_BAUD_RATE);
  webLogService.begin(&Serial);
  Log.begin(LOG_LEVEL_VERBOSE, webLogService.output);

  // start the framework and demo project
  esp8266React.begin();

  // start the services
  liftCommandService.begin();
  liftSettingsService.begin();
  liftStatusService.begin();

  // start the server
  server.begin();

  //turn off LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  //update the framework
  esp8266React.loop();
  //update services
  liftCommandService.loop();
  liftStatusService.loop();
}

#include <ESP8266React.h>
#include <LightStateService.h>

#define SERIAL_BAUD_RATE 115200

AsyncWebServer server(80);
ESP8266React esp8266React(&server);
LightStateService lightStateService = LightStateService(&server, esp8266React.getSecurityManager());

void setup() {
  // start serial and filesystem
  Serial.begin(SERIAL_BAUD_RATE);

  // start the framework and demo project
  esp8266React.begin();

  // load the initial light settings
  lightStateService.begin();

  // start the server
  server.begin();
}

void loop() {
  // run the framework's loop function
  esp8266React.loop();
}

#include <OTASettingsService.h>

OTASettingsService::OTASettingsService(AsyncWebServer* server, FS* fs, SecurityManager* securityManager) :
    _httpEndpoint(OTASettings::read, OTASettings::update, this, server, OTA_SETTINGS_SERVICE_PATH, securityManager),
    _fsPersistence(OTASettings::read, OTASettings::update, this, fs, OTA_SETTINGS_FILE),
    _arduinoOTA(nullptr) {
#ifdef ESP32
  WiFi.onEvent(std::bind(&OTASettingsService::onStationModeGotIP, this, std::placeholders::_1, std::placeholders::_2),
               WiFiEvent_t::SYSTEM_EVENT_STA_GOT_IP);
#elif defined(ESP8266)
  _onStationModeGotIPHandler =
      WiFi.onStationModeGotIP(std::bind(&OTASettingsService::onStationModeGotIP, this, std::placeholders::_1));
#endif
  addUpdateHandler([&](const String& originId) { configureArduinoOTA(); }, false);
}

void OTASettingsService::begin() {
  _fsPersistence.readFromFS();
  configureArduinoOTA();
}

void OTASettingsService::loop() {
  if (_state.enabled && _arduinoOTA) {
    _arduinoOTA->handle();
    MDNS.update();
  }
}

void OTASettingsService::configureArduinoOTA() {
  if (_arduinoOTA) {
#ifdef ESP32
    _arduinoOTA->end();
#endif
    delete _arduinoOTA;
    _arduinoOTA = nullptr;
  }
  if (_state.enabled) {
    //Log.trace(F("Starting OTA Update Service..." CR));
    _arduinoOTA = new ArduinoOTAClass;
    _arduinoOTA->setPort(_state.port);
    _arduinoOTA->setPassword(_state.password.c_str());
    _arduinoOTA->onStart([]() { Log.trace(F("Starting" CR)); });
    _arduinoOTA->onEnd([]() { Log.trace(F("\r\nEnd" CR)); });
    _arduinoOTA->onProgress([](unsigned int progress, unsigned int total) {
    //  Log.trace(PSTR("Progress: %u%%\r\n"), (progress / (total / 100)));
    });
    // _arduinoOTA->onError([](ota_error_t error) {
    //   Log.trace("Error[%u]: ", error);
    //   if (error == OTA_AUTH_ERROR)
    //     Log.trace(F("Auth Failed" CR));
    //   else if (error == OTA_BEGIN_ERROR)
    //     Log.trace(F("Begin Failed" CR));
    //   else if (error == OTA_CONNECT_ERROR)
    //     Log.trace(F("Connect Failed" CR));
    //   else if (error == OTA_RECEIVE_ERROR)
    //     Log.trace(F("Receive Failed" CR));
    //   else if (error == OTA_END_ERROR)
    //     Log.trace(F("End Failed" CR));
    // });
    _arduinoOTA->setHostname(WiFi.hostname().c_str());
    _arduinoOTA->begin();
  }
}

#ifdef ESP32
void OTASettingsService::onStationModeGotIP(WiFiEvent_t event, WiFiEventInfo_t info) {
  configureArduinoOTA();
}
#elif defined(ESP8266)
void OTASettingsService::onStationModeGotIP(const WiFiEventStationModeGotIP& event) {
  configureArduinoOTA();
}
#endif

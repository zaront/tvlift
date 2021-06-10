#include <LiftSettingsService.h>

LiftSettingsService::LiftSettingsService(AsyncWebServer* server, FS* fs, SecurityManager* securityManager) :
    _httpEndpoint(LiftSettings::read,
                  LiftSettings::update,
                  this,
                  server,
                  LIFT_SETTINGS_ENDPOINT,
                  securityManager,
                  AuthenticationPredicates::IS_AUTHENTICATED),
    _fsPersistence(LiftSettings::read, 
                  LiftSettings::update, 
                  this, 
                  fs, 
                  LIFT_SETTINGS_FILE) {
  
  // configure settings service update handler to update LED state
  addUpdateHandler([&](const String& originId) { onConfigUpdated(); }, false);
}

void LiftSettingsService::begin() {
  //initial values
  _fsPersistence.readFromFS();
  onConfigUpdated();
}

void LiftSettingsService::onConfigUpdated() {
  //settings changed
  Log.verbose("settings changed" CR);
}

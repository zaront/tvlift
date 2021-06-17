#include <LiftSettingsService.h>

LiftSettingsService::LiftSettingsService(AsyncWebServer* server, FS* fs, SecurityManager* securityManager, Lift* lift) :
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
  
  _lift = lift;

  // configure settings service update handler to update LED state
  addUpdateHandler([&](const String& originId) { onConfigUpdated(); }, false);
}

void LiftSettingsService::begin() {
  //initial values
  _fsPersistence.readFromFS();
  onConfigUpdated();
}

void LiftSettingsService::onConfigUpdated() {

  //update lift settings
  _lift->motor.setAcceleration(_state.acceleration);
  _lift->minPosition = _state.minPosition;
  _lift->maxPosition = _state.maxPosition;

  Log.verbose("settings changed" CR);
}

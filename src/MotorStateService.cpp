#include <MotorStateService.h>

MotorStateService::MotorStateService(AsyncWebServer *server, SecurityManager *securityManager) :
    _httpEndpoint(MotorState::read,
                  MotorState::update,
                  this,
                  server,
                  MOTOR_SETTINGS_ENDPOINT_PATH,
                  securityManager,
                  AuthenticationPredicates::IS_AUTHENTICATED),
    _webSocket(MotorState::read,
               MotorState::update,
               this,
               server,
               MOTOR_SETTINGS_SOCKET_PATH,
               securityManager,
               AuthenticationPredicates::IS_AUTHENTICATED) {
  // configure led to be output
  pinMode(LED_PIN, OUTPUT);

  // configure settings service update handler to update LED state
  addUpdateHandler([&](const String &originId) { onConfigUpdated(); }, false);
}

void MotorStateService::begin() {
  _state.ledOn = DEFAULT_LED_STATE;
  onConfigUpdated();
}

void MotorStateService::onConfigUpdated() {
  digitalWrite(LED_PIN, _state.ledOn ? LED_ON : LED_OFF);
}

#include <LiftCommandService.h>

LiftCommandService::LiftCommandService(AsyncWebServer *server, SecurityManager *securityManager) :
    _webSocket(LiftCommand::read,
                  LiftCommand::update,
                  this,
                  server,
                  LIFT_COMMAND_ENDPOINT,
                  securityManager,
                  AuthenticationPredicates::IS_AUTHENTICATED) {
  // configure led to be output
  pinMode(LED_PIN, OUTPUT);

  // configure settings service update handler to update LED state
  addUpdateHandler([&](const String &originId) { onConfigUpdated(); }, false);
}

void LiftCommandService::begin() {
  _state.command = LiftCommandType::none;
  _state.amount = 0;
  onConfigUpdated();
}

void LiftCommandService::onConfigUpdated() {
  Log.verbose("command received: %d" CR, _state.command);
  digitalWrite(LED_PIN, _state.command == LiftCommandType::nudge_up ? LED_ON : LED_OFF);
}

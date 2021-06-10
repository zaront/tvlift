#include <LiftStatusService.h>

LiftStatusService::LiftStatusService(AsyncWebServer *server, SecurityManager *securityManager) :
    _webSocket(LiftStatus::read,
                  LiftStatus::update,
                  this,
                  server,
                  LIFT_STATUS_ENDPOINT,
                  securityManager,
                  AuthenticationPredicates::IS_AUTHENTICATED) {

  // configure settings service update handler to update LED state
  addUpdateHandler([&](const String &originId) { onConfigUpdated(); }, false);
}

void LiftStatusService::begin() {

  // configure the button
  _button.attach(BUTTON_PIN, INPUT_PULLUP);
  _button.interval(BUTTON_BOUNCE_INTERVAL);
  _button.setPressedState(LOW);

  //initial state
  _state.motorState = MotorStatus::off;
  _state.position = 0;
  _state.position = false;
  _state.chromecastStatus = "";
  _state.buttonPressed = false;
  _state.limitSwitchPressed = false;
  onConfigUpdated();
}

void LiftStatusService::onConfigUpdated() {

}

void LiftStatusService::loop() {
  
  //button event
  _button.update();
  if (_button.changed()) {
    //update button state
    update([&](LiftStatus& state) {
      if (state.buttonPressed != _button.pressed())
      {
        state.buttonPressed = _button.pressed();
        Log.verbose("hidden button pressed: %T" CR, state.buttonPressed);
        return StateUpdateResult::CHANGED;
      }
      return StateUpdateResult::UNCHANGED;
    },"tvlift");
  }
}

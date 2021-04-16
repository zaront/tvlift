#include <ButtonStateService.h>

ButtonStateService::ButtonStateService(AsyncWebServer* server, SecurityManager* securityManager) :
    _webSocket(ButtonState::read,
               ButtonState::update,
               this,
               server,
               BUTTON_URL,
               securityManager,
               AuthenticationPredicates::IS_AUTHENTICATED) {
  // event handler
  addUpdateHandler([&](const String& originId) { onConfigUpdated(); }, false);
}

void ButtonStateService::begin() {
  // configure the button
  _button.attach(BUTTON_PIN, INPUT_PULLUP);
  _button.interval(BUTTON_BOUNCE_INTERVAL);
  _button.setPressedState(LOW);

  _state.buttonPressed = false;
}

void ButtonStateService::onConfigUpdated() {
  // do something when stuff changes
}

void ButtonStateService::loop() {
  _button.update();

  if (_button.changed()) {
    StaticJsonDocument<256> doc;
    JsonObject state = doc.to<JsonObject>();
    this->read(state, ButtonState::read);
    state["button_pressed"] = _button.pressed();
    this->update(state, ButtonState::update, "button");
    Log.verbose("button pressed: %T" CR, _button.pressed());
  }
}

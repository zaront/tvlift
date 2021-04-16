#include <ButtonStateService.h>

ButtonStateService::ButtonStateService(AsyncWebServer *server, SecurityManager *securityManager) :
    _webSocket(ButtonState::read,
               ButtonState::update,
               this,
               server,
               BUTTON_URL,
               securityManager,
               AuthenticationPredicates::IS_AUTHENTICATED) {

  // event handler
  addUpdateHandler([&](const String &originId) { onConfigUpdated(); }, false);
}

void ButtonStateService::begin() {

  // configure the button
  _button.attach(BUTTON_PIN, INPUT_PULLUP);
  _button.interval(BUTTON_BOUNCE_INTERVAL);
  _button.setPressedState(LOW);

  _state.buttonPressed = false;
}

void ButtonStateService::onConfigUpdated() {
  //do something when stuff changes
}

void ButtonStateService::loop() {
  _button.update();

  //Serial.printf("button state: %d\n", _button.isPressed());

  if (_button.changed()) {
    Serial.print("button pressed: ");
    if (_button.rose())
      Serial.println("true");
    else
      Serial.println("false");
    JsonObject state;
    this->read(state, ButtonState::read);
    state["button_pressed"] = _button.rose();
    this->update(state, ButtonState::update, "button");
  }
}

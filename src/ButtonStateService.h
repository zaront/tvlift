#ifndef ButtonStateService_h
#define ButtonStateService_h

#include <Arduino.h>
#include <HttpEndpoint.h>
#include <WebSocketTxRx.h>
#include <Bounce2.h>

#define BUTTON_PIN D3
#define BUTTON_BOUNCE_INTERVAL 30

#define BUTTON_URL "/ws/buttonState"

class ButtonState {
 public:
  bool buttonPressed;

  static void read(ButtonState &state, JsonObject &root) {
    root["button_pressed"] = state.buttonPressed;
  }

  static StateUpdateResult update(JsonObject &root, ButtonState &state) {
    boolean buttonPressed = root["button_pressed"] | false;
    if (state.buttonPressed != buttonPressed) {
      state.buttonPressed = buttonPressed;
      return StateUpdateResult::CHANGED;
    }
    return StateUpdateResult::UNCHANGED;
  }
};

class ButtonStateService : public StatefulService<ButtonState> {
 public:
  ButtonStateService(AsyncWebServer *server, SecurityManager *securityManager);
  void begin();
  void loop();

 private:
  WebSocketTxRx<ButtonState> _webSocket;
  Bounce2::Button _button;

  void onConfigUpdated();
};

#endif

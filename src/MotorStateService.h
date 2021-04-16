#ifndef MotorStateService_h
#define MotorStateService_h

#include <HttpEndpoint.h>
#include <WebSocketTxRx.h>

#define LED_PIN 2

#define DEFAULT_LED_STATE false

// Note that the built-in LED is on when the pin is low on most NodeMCU boards.
// This is because the anode is tied to VCC and the cathode to the GPIO 4 (Arduino pin 2).
#ifdef ESP32
#define LED_ON 0x1
#define LED_OFF 0x0
#elif defined(ESP8266)
#define LED_ON 0x0
#define LED_OFF 0x1
#endif

#define MOTOR_SETTINGS_ENDPOINT_PATH "/rest/motorState"
#define MOTOR_SETTINGS_SOCKET_PATH "/ws/motorState"

class MotorState {
 public:
  bool ledOn;

  static void read(MotorState &settings, JsonObject &root) {
    root["led_on"] = settings.ledOn;
  }

  static StateUpdateResult update(JsonObject &root, MotorState &state) {
    boolean newState = root["led_on"] | DEFAULT_LED_STATE;
    if (state.ledOn != newState) {
      state.ledOn = newState;
      return StateUpdateResult::CHANGED;
    }
    return StateUpdateResult::UNCHANGED;
  }
};

class MotorStateService : public StatefulService<MotorState> {
 public:
  MotorStateService(AsyncWebServer *server, SecurityManager *securityManager);
  void begin();

 private:
  HttpEndpoint<MotorState> _httpEndpoint;
  WebSocketTxRx<MotorState> _webSocket;

  void onConfigUpdated();
};

#endif

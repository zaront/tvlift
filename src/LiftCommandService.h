#ifndef LiftCommandService_h
#define LiftCommandService_h

#include <WebSocketTxRx.h>
#include <ArduinoLog.h>

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

#define LIFT_COMMAND_ENDPOINT "/ws/liftCommand"

enum class LiftCommandType { none, up, down, nudge_up, nudge_down, stop, motor_off, tv_on, tv_off, automatic };
static const char* LiftCommandType_str[] = {"none", "up", "down", "nudge_up", "nudge_down", "stop", "motor_off", "tv_on", "tv_off", "automatic"};

class LiftCommand {
  static LiftCommandType toCommand(const char* command) {
    for (size_t i = 0; i < sizeof(LiftCommandType_str); i++)
      if (strcmp(command, LiftCommandType_str[i]) == 0)
        return static_cast<LiftCommandType>(i);
    return LiftCommandType::none;
  }

  static const char* fromCommand(LiftCommandType command) {
    return LiftCommandType_str[static_cast<int>(command)];
  }

 public:
  LiftCommandType command;
  int amount;

  static void read(LiftCommand& settings, JsonObject& root) {
    root["command"] = fromCommand(settings.command);
    root["amount"] = settings.amount;
  }

  static StateUpdateResult update(JsonObject& root, LiftCommand& state) {
    StateUpdateResult result = StateUpdateResult::UNCHANGED;

    // update command
    LiftCommandType command = toCommand(root["command"]);
    if (state.command != command) {
      state.command = command;
      result = StateUpdateResult::CHANGED;
    }

    // update amount
    int amount = root["amount"] | 0;
    if (state.amount != amount) {
      state.amount = amount;
      result = StateUpdateResult::CHANGED;
    }

    return result;
  }
};

class LiftCommandService : public StatefulService<LiftCommand> {
 public:
  LiftCommandService(AsyncWebServer* server, SecurityManager* securityManager);
  void begin();

 private:
  WebSocketTxRx<LiftCommand> _webSocket;

  void onConfigUpdated();
};

#endif

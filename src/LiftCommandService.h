#ifndef LiftCommandService_h
#define LiftCommandService_h

#include <WebSocketTxRx.h>
#include <ArduinoLog.h>
#include <Lift.h>

#define LIFT_COMMAND_ENDPOINT "/ws/liftCommand"

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

  bool operator==(const LiftCommand& obj) const {
    return command == obj.command && 
            amount == obj.amount;
  }

  static void read(LiftCommand& settings, JsonObject& root) {
    root["command"] = fromCommand(settings.command);
    root["amount"] = settings.amount;
  }

  static StateUpdateResult update(JsonObject& root, LiftCommand& state) {
    LiftCommand newState = {};
    newState.command = toCommand(root["command"]);
    newState.amount= root["amount"];

    if (newState == state) {
      return StateUpdateResult::UNCHANGED;
    }
    state = newState;
    return StateUpdateResult::CHANGED;
  }
};

class LiftCommandService : public StatefulService<LiftCommand> {
 public:
  LiftCommandService(AsyncWebServer* server, SecurityManager* securityManager, Lift* lift);
  void begin();
  void loop();

 private:
  WebSocketTxRx<LiftCommand> _webSocket;
  Lift* _lift;

  void onConfigUpdated();
};

#endif

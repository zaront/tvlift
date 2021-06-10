#ifndef LiftStatusService_h
#define LiftStatusService_h

#include <WebSocketTxRx.h>
#include <ArduinoLog.h>
#include <Bounce2.h>

#define BUTTON_PIN D3
#define BUTTON_BOUNCE_INTERVAL 30

#define LIFT_STATUS_ENDPOINT "/ws/liftStatus"

enum class MotorStatus { off, stopped, raising, lowering };
static const char* MotorStatus_str[] = {"off", "stopped", "raising", "lowering"};

class LiftStatus {
  static MotorStatus toMotorStatus(const char* value) {
    for (size_t i = 0; i < sizeof(MotorStatus_str); i++)
      if (strcmp(value, MotorStatus_str[i]) == 0)
        return static_cast<MotorStatus>(i);
    return MotorStatus::off;
  }

  static const char* fromMotorStatus(MotorStatus value) {
    return MotorStatus_str[static_cast<int>(value)];
  }

 public:
  MotorStatus motorState;
  int position;
  boolean sendingTvCode;
  String chromecastStatus;
  boolean buttonPressed;
  boolean limitSwitchPressed;

  bool operator==(const LiftStatus& obj) const {
    return motorState == obj.motorState && 
            position == obj.position &&
            sendingTvCode == obj.sendingTvCode &&
            chromecastStatus == obj.chromecastStatus &&
            buttonPressed == obj.buttonPressed &&
            limitSwitchPressed == obj.limitSwitchPressed;
  }

  static void read(LiftStatus& state, JsonObject& root) {
    root["motorState"] = fromMotorStatus(state.motorState);
    root["position"] = state.position;
    root["sendingTvCode"] = state.sendingTvCode;
    root["chromecastStatus"] = state.chromecastStatus;
    root["buttonPressed"] = state.buttonPressed;
    root["limitSwitchPressed"] = state.limitSwitchPressed;
  }

  static StateUpdateResult update(JsonObject& root, LiftStatus& state) {
    LiftStatus newState = {};
    newState.motorState = toMotorStatus(root["motorState"]);
    state.position = root["position"];
    state.sendingTvCode = root["sendingTvCode"];
    state.chromecastStatus = root["chromecastStatus"].as<String>();
    state.buttonPressed = root["buttonPressed"];
    state.limitSwitchPressed = root["limitSwitchPressed"];

    if (newState == state) {
      return StateUpdateResult::UNCHANGED;
    }
    state = newState;
    return StateUpdateResult::CHANGED;
  }
};

class LiftStatusService : public StatefulService<LiftStatus> {
 public:
  LiftStatusService(AsyncWebServer* server, SecurityManager* securityManager);
  void begin();
  void loop();

 private:
  WebSocketTxRx<LiftStatus> _webSocket;
  ulong _startTime = 0;
  ulong _timer = 0;
  Bounce2::Button _button;

  void onConfigUpdated();
};

#endif

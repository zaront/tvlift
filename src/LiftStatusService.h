#ifndef LiftStatusService_h
#define LiftStatusService_h

#include <WebSocketTxRx.h>
#include <ArduinoLog.h>
#include <Lift.h>

#define LIFT_STATUS_ENDPOINT "/ws/liftStatus"

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
  LiftStatusService(AsyncWebServer* server, SecurityManager* securityManager, Lift* lift);
  void begin();
  void loop();

 private:
  WebSocketTxRx<LiftStatus> _webSocket;
  Lift* _lift;
  void onConfigUpdated();
  MotorStatus getMotorState();
};

#endif

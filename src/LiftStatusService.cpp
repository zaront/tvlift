#include <LiftStatusService.h>

LiftStatusService::LiftStatusService(AsyncWebServer *server, SecurityManager *securityManager, Lift* lift) :
    _webSocket(LiftStatus::read,
                  LiftStatus::update,
                  this,
                  server,
                  LIFT_STATUS_ENDPOINT,
                  securityManager,
                  AuthenticationPredicates::IS_AUTHENTICATED) {

  _lift = lift;

  // configure settings service update handler to update LED state
  addUpdateHandler([&](const String &originId) { onConfigUpdated(); }, false);
}

void LiftStatusService::begin() {
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

MotorStatus LiftStatusService::getMotorState ()
{
  return MotorStatus::off;
}

void LiftStatusService::loop() {
  
  //calculate new status
  LiftStatus newState = {};
  newState.buttonPressed = _lift->button.isPressed();
  newState.limitSwitchPressed = _lift->limitSwitch.isPressed();
  newState.position = _lift->motor.currentPosition();
  newState.sendingTvCode = false;
  newState.chromecastStatus = "not configured";
  newState.motorState = getMotorState();

  //update status
  if (!(newState == _state))
  {
    update([&](LiftStatus& state) {
      state.motorState = newState.motorState;
      state.position = newState.position;
      state.sendingTvCode = newState.sendingTvCode;
      state.chromecastStatus = newState.chromecastStatus;
      state.buttonPressed = newState.buttonPressed;
      state.limitSwitchPressed = newState.limitSwitchPressed;
      return StateUpdateResult::CHANGED;
    },"tvlift");
  }
}

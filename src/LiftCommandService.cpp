#include <LiftCommandService.h>

LiftCommandService::LiftCommandService(AsyncWebServer *server, SecurityManager *securityManager, Lift* lift) :
    _webSocket(LiftCommand::read,
                  LiftCommand::update,
                  this,
                  server,
                  LIFT_COMMAND_ENDPOINT,
                  securityManager,
                  AuthenticationPredicates::IS_AUTHENTICATED) {

  _lift = lift;

  // configure settings service update handler to update LED state
  addUpdateHandler([&](const String &originId) { onConfigUpdated(); }, false);
}

void LiftCommandService::begin() {
  _state.command = LiftCommandType::none;
  _state.amount = 0;
  onConfigUpdated();
}

void LiftCommandService::onConfigUpdated() {

  if (_state.command == LiftCommandType::nudge_up)
  {
    Log.verbose("nudging UP by %d" CR, _state.amount);
    _lift->motor.enableOutputs();
    _lift->motor.move(_state.amount);
  }
  else if (_state.command == LiftCommandType::nudge_down)
  {
    Log.verbose("nudging DOWN by %d" CR, _state.amount);
    _lift->motor.enableOutputs();
    _lift->motor.move(-_state.amount);
  }
  else if (_state.command == LiftCommandType::stop)
  {
    _lift->motor.enableOutputs();
    _lift->motor.stop();
  }
  else if (_state.command == LiftCommandType::motor_off)
  {
    _lift->motor.stop();
    _lift->motor.disableOutputs();
  }
  else if (_state.command == LiftCommandType::none)
  {
    Log.verbose("idle" CR);
  }
}

void LiftCommandService::loop() {
  //go to idle command
  if ((_state.command == LiftCommandType::automatic ||
    _state.command == LiftCommandType::down ||
    _state.command == LiftCommandType::up ||
    _state.command == LiftCommandType::nudge_down ||
    _state.command == LiftCommandType::nudge_up ||
     _state.command == LiftCommandType::motor_off ||
    _state.command == LiftCommandType::stop ) &&
    !_lift->motor.isRunning())
  {
    update([&](LiftCommand& state) {
      if (state.command != LiftCommandType::none)
      {
        state.command = LiftCommandType::none;
        return StateUpdateResult::CHANGED;
      }
      return StateUpdateResult::UNCHANGED;
    },"tvlift");
  }
}

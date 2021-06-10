#include <LiftCommandService.h>

LiftCommandService::LiftCommandService(AsyncWebServer *server, SecurityManager *securityManager) :
    _webSocket(LiftCommand::read,
                  LiftCommand::update,
                  this,
                  server,
                  LIFT_COMMAND_ENDPOINT,
                  securityManager,
                  AuthenticationPredicates::IS_AUTHENTICATED) {

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
    _startTime = millis();
    _timer = _state.amount;
  }
  else if (_state.command == LiftCommandType::nudge_down)
  {
    Log.verbose("nudging DOWN by %d" CR, _state.amount);
    _startTime = millis();
    _timer = _state.amount;
  }
  else if (_state.command == LiftCommandType::none)
  {
    Log.verbose("idle" CR);
  }
}

void LiftCommandService::loop() {
  //go to idle command
  if (_startTime != 0 && (millis() - _startTime) >= _timer)
  {
    _startTime = 0;
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

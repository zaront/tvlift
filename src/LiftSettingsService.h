#ifndef LiftSettingsService_h
#define LiftSettingsService_h

#include <HttpEndpoint.h>
#include <FSPersistence.h>
#include <ArduinoLog.h>
#include <Lift.h>

#define LIFT_SETTINGS_ENDPOINT "/rest/liftSettings"
#define LIFT_SETTINGS_FILE "/config/liftSettings.json"

class LiftSettings {
 public:
  int maxPosition;
  int minPosition;
  int maxSpeed;
  float acceleration;
  int disconnectTimeout;
  String tvCodeOn;
  String tvCodeOff;
  String chromecast;

  bool operator==(const LiftSettings& obj) const {
    return maxPosition == obj.maxPosition && 
            minPosition == obj.minPosition && 
            maxSpeed == obj.maxSpeed &&
            acceleration == obj.acceleration && 
            disconnectTimeout == obj.disconnectTimeout && 
            tvCodeOn == obj.tvCodeOn &&
            tvCodeOff == obj.tvCodeOff && 
            chromecast == obj.chromecast;
  }

  static void read(LiftSettings& settings, JsonObject& root) {
    root["maxPosition"] = settings.maxPosition;
    root["minPosition"] = settings.minPosition;
    root["maxSpeed"] = settings.maxSpeed;
    root["acceleration"] = settings.acceleration;
    root["disconnectTimeout"] = settings.disconnectTimeout;
    root["tvCodeOn"] = settings.tvCodeOn;
    root["tvCodeOff"] = settings.tvCodeOff;
    root["chromecast"] = settings.chromecast;
  }

  static StateUpdateResult update(JsonObject& root, LiftSettings& state) {
    LiftSettings newState = {};
    newState.maxPosition = root["maxPosition"];
    newState.minPosition= root["minPosition"];
    newState.maxSpeed = root["maxSpeed"];
    newState.acceleration = root["acceleration"];
    newState.disconnectTimeout = root["disconnectTimeout"];
    newState.tvCodeOn = root["tvCodeOn"].as<String>();
    newState.tvCodeOff = root["tvCodeOff"].as<String>();
    newState.chromecast = root["chromecast"].as<String>();

    if (newState == state) {
      return StateUpdateResult::UNCHANGED;
    }
    state = newState;
    return StateUpdateResult::CHANGED;
  };
};

class LiftSettingsService : public StatefulService<LiftSettings> {
 public:
  LiftSettingsService(AsyncWebServer* server, FS* fs, SecurityManager* securityManager, Lift* lift);
  void begin();

 private:
  HttpEndpoint<LiftSettings> _httpEndpoint;
  FSPersistence<LiftSettings> _fsPersistence;
  Lift* _lift;

  void onConfigUpdated();
};

#endif

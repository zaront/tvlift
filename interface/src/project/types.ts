export interface LightState {
  led_on: boolean;
}

export interface MotorState {
  led_on: boolean;
}

export interface ButtonState {
  button_pressed: boolean;
}

export interface LiftCommand {
  command:
    | "none"
    | "up"
    | "down"
    | "nudge_up"
    | "nudge_down"
    | "stop"
    | "motor_off"
    | "tv_on"
    | "tv_off"
    | "automatic";
  amount: number;
}

export interface LiftState {
  motorState: "off" | "stopped" | "raising" | "lowering";
  position: number;
  sendingTvCode: boolean;
  chromecastStatus: string;
  buttonPressed: boolean;
  limitSwitchPressed: boolean;
}

export interface LiftSettings {
  maxPosition: number;
  minPosition: number;
  maxSpeed: number;
  acceleration: number;
  disconnectTimeout: number;
  tvCodeOn: string;
  tvCodeOff: string;
  chromecast: string;
}

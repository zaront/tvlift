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
  liftStatus: "raising" | "lowering" | "stopped";
  sendingOffCommand: boolean;
  position: number;
  chromecastStatus: string;
  buttonPressed: boolean;
}

export interface LiftSettings {
  maxPosition: number;
  minPosition: number;
  maxSpeed: number;
  acceleration: number;
  disconnectTimeout: number;
  tvCode: string;
  chromecast: string;
}

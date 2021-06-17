#ifndef Lift_h
#define Lift_h

#include <ArduinoLog.h>
#include <Bounce2.h>
//#include <Encoder.h>
#include <AccelStepper.h>

#define BUTTON_PIN D3
#define LIMIT_SWITCH_PIN D4
#define BUTTON_BOUNCE_INTERVAL 30

#define MOTOR_STEP_PIN D5
#define MOTOR_DIRECTION_PIN D6
#define MOTOR_ENABLE_PIN D7

#define ENCODER_A_PIN D0
#define ENCODER_B_PIN D1

class Lift {

public:
    Lift();
    void begin();
    void loop();

    Bounce2::Button button;
    Bounce2::Button limitSwitch;
    //Encoder encoder;
    AccelStepper motor;
    //LiftCommandType currentCommand;
    //MotorStatus motorStatus;

    double minPosition;
    double maxPosition;

};

enum class LiftCommandType { none, up, down, nudge_up, nudge_down, stop, motor_off, tv_on, tv_off, automatic };

enum class MotorStatus { off, stopped, raising, lowering };

#endif

#include <Lift.h>

Lift::Lift() :
  //encoder(ENCODER_A_PIN, ENCODER_B_PIN),
  motor(AccelStepper::DRIVER, MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN)
{
  // configure the button
  button.attach(BUTTON_PIN, INPUT_PULLUP);
  button.interval(BUTTON_BOUNCE_INTERVAL);
  button.setPressedState(LOW);

   // configure the limit switch
  limitSwitch.attach(LIMIT_SWITCH_PIN, INPUT_PULLUP);
  limitSwitch.interval(BUTTON_BOUNCE_INTERVAL);
  limitSwitch.setPressedState(LOW);

  //configure the motor
  motor.setEnablePin(MOTOR_ENABLE_PIN);
}

void Lift::begin() {
  //currentCommand = LiftCommandType::none;
  //motorStatus = MotorStatus::off;
}

void Lift::loop() {
  //update buttons
  button.update();
  limitSwitch.update();

  //update the motor
  motor.run();
}

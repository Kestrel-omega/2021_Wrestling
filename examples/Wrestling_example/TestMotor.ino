#include "Wrestling_Header.h"

void setup()
{
  void InitMotorControl(void); // Initialize motor settings

  // Motor control library
  void SetPWMfrequency(int freq);                // Set motor PWM frequency
  void MotorActiveStatus(int side, bool status); // Set motor turn on/off
  void SetMotorSpeed(int side, byte pwm);        // Set motor PWM
  void StopMotor(int side);

  SetPWMfrequency(0x02); // need to check

  MotorActiveStatus(R1, true);
  MotorActiveStatus(R2, true);
  MotorActiveStatus(L1, true);
  MotorActiveStatus(L2, true);
}

void loop()
{

  // Set motor PWM
  SetMotorSpeed(R1, 0);
  SetMotorSpeed(R2, 0);
  SetMotorSpeed(L1, 0);
  SetMotorSpeed(L2, 0);

  // Stop motor
  StopMotor(R1);
  StopMotor(R2);
  StopMotor(L1);
  StopMotor(L2);

  while (1)
  {
    SetMotorSpeed(R1, 255);
    SetMotorSpeed(R1, 255);
  }
}

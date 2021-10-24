#include "motor.hpp"

// Motor control library
void InitMotor()
{
	for(int i=6;i<14;i++)
	{
		pinMode(i,OUTPUT);
		digitalWrite(i,LOW);
	}
}

void StopMotor() // shut down all motor
{
	digitalWrite(R_EN1,LOW);
	digitalWrite(L_EN1,LOW);
	digitalWrite(R_EN2,LOW);
	digitalWrite(L_EN2,LOW);
	analogWrite(R_PWM1,0);
	analogWrite(L_PWM1,0);
	analogWrite(R_PWM2,0);
	analogWrite(L_PWM2,0);
}

void MotorActiveStatus(int a) // Set motor turn on/off
{
	if(a == 1)
	{
		digitalWrite(R_EN1,HIGH);
		digitalWrite(L_EN1,HIGH);
		digitalWrite(R_EN2,HIGH);
		digitalWrite(L_EN2,HIGH);
	}
	
	else if(a==0)
	{
		digitalWrite(R_EN1,LOW);
		digitalWrite(L_EN1,LOW);
		digitalWrite(R_EN2,LOW);
		digitalWrite(L_EN2,LOW);
	}

}

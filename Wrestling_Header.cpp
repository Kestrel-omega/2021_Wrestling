#include "Wrestling_Header.h"

// IR sensor library
float ReadIRSensor(int idx) // Read IR sensor to get a distance from obstacles
{
	float sensorValue = 0;

	switch (idx)
	{
		case 0:
		sensorValue = analogRead(IR1);
		break;

		case 1:
		sensorValue = analogRead(IR2);
		break;

		case 2:
		sensorValue = analogRead(IR3);
		break;

		case 3:
		sensorValue = analogRead(IR4);
		break;
	}
	float cm = 10650.08 * pow(sensorValue, -0.935) - 10; // need to check

	return cm;
}

bool IR_safe()
{
	return ReadIRSensor(1) >= 25  && ReadIRSensor(2) >= 25  && ReadIRSensor(3) >= 25;
}

// Color sensor library
struct Color ReadColorSensor(struct Adafruit_TCS34725softi2c tcs) // Read color sensor in r, g, b value
{
	uint16_t clear, red, green, blue;
	uint32_t sum = clear;
	float r, g ,b;


	Color color;
	tcs.setInterrupt(false);
	delay(30);

	tcs.getRawData(&red, &green, &blue, &clear);
	tcs.setInterrupt(true);
	
	r = red ; r /= 256;
	g = green; g /=256;
	b = blue; b/= 256;
	
	

	color.red = red;
	color.green = green;
	color.blue = blue;
	
	return color;
}

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
	analogWrite(PWM_LF,0);
	analogWrite(PWM_LB,0);
	analogWrite(PWM_RF,0);
	analogWrite(PWM_RB,0);
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

// Initialize
void InitIRSensor() // Initialize IR sensors
{
	pinMode(IR1, INPUT);
	pinMode(IR2, INPUT);
	pinMode(IR3, INPUT);
	pinMode(IR4, INPUT);
}

void InitCamSerial(struct SoftwareSerial mySerial, int baudrate) // Initialize jetson - arduino serial communication settings
{
	Serial.begin(baudrate);
	mySerial.begin(baudrate);
}
void InitBot(struct SoftwareSerial mySerial, int baudrate) // Initialize all of things
{
	InitIRSensor();
	InitColorSensor();
	InitCamSerial(mySerial, baudrate);
}

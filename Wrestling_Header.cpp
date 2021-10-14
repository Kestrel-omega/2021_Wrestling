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

void IR_safe()
{
	ReadIRSensor(1) >= 25  && ReadIRSensor(2) >= 25  && ReadIRSensor(3) >= 25;
}
}
}

// Color sensor library
struct Color ReadColorSensor(struct Adafruit_TCS34725softi2c tcs) // Read color sensor in r, g, b value
{
	uint16_t clear, red, green, blue;
	uint32_t sum = clear;
	float r, g ,b;


	Color color;
	tcs.setInterrupt(false);
	delay(60);

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

void Color_black()
{
	color[0].red < 000 &&  color[0].blue < 000 && color[1].red < 000 &&  color[1].blue < 000 && color[2].red < 000 &&  color[2].blue < 000 && color[3].red < 000 &&  color[3].blue < 000 ; 
}

void Color_red_front()
{
	return (color[0].red>123) || (color[1].red >123); // red 수정필요	
}

void Color_red_back()
{
	return (color[2].red>123) || (color[3].red >123);//red 수정필요
}

void Color_left()
{
	return (color[0].red > 123 || color[0].blue > 123 || color[2].red > 123 || color[2].blue > 123) ;
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

// Camera serial library
void ReadCamData(struct SoftwareSerial mySerial, int &x_value, int &y_value, int &size_value) // Read camera data from jetson nano
{
	char Buffer[30];

	if (mySerial.available())
	{
		String inString = mySerial.readStringUntil('\n');

		int index1 = inString.indexOf(',');
		int index2 = inString.indexOf(',', index1 + 1);
		int index3 = inString.indexOf(',', index2 + 1);
		int index4 = inString.indexOf(',', index3 + 1);
		int index5 = inString.indexOf(',', index4 + 1);

		int inString1 = inString.substring(0, index1).toInt();
		int inString2 = inString.substring(index1 + 1, index2).toInt();
		int inString3 = inString.substring(index2 + 1, index3).toInt();
		int inString4 = inString.substring(index3 + 1, index4).toInt();
		int inString5 = inString.substring(index4 + 1, index5).toInt();

		if (inString1 == -1 && inString5 == -2)
		{
			sprintf(Buffer, "x : %d, y : %d, size : %d \n", inString2, inString3, inString4);
			x_value = inString2;
			y_value = inString3;
			size_value = inString4;
			Serial.print(Buffer);
		}
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
void InitColorSensor(void) // Initialize color sensors
{
	// Actually, Color sensor is no need to initialize
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

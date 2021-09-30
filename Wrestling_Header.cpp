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

// Color sensor library
struct Color ReadColorSensor(struct Adafruit_TCS34725softi2c tcs) // Read color sensor in r, g, b value
{
    uint16_t c, r, g, b;
    Color color;
    
    tcs.getRawData(&r, &g, &b, &c);
    color.red = (float)r;
    color.green = (float)g;
    color.blue = (float)b;
    
    return color;
}

// Motor control library
void SetPWMfrequency(int freq) // Set motor PWM frequency
{
    TCCR0B = TCCR0B & 0b11111000 | freq; // need to check
}
void MotorActiveStatus(int side, bool status) // Set motor turn on/off
{
    switch (side)
    {
    case R1:
        digitalWrite(R_EN1, status);
        break;
    case R2:
        digitalWrite(R_EN2, status);
        break;
    case L1:
        digitalWrite(L_EN1, status);
        break;
    case L2:
        digitalWrite(L_EN2, status);
        break;
    default:
        break;
    }
}
void SetMotorSpeed(int side, byte pwm) // Set motor PWM
{
    switch (side)
    {
    case R1:
        digitalWrite(RPWM1, pwm);
        break;
    case R2:
        digitalWrite(RPWM2, pwm);
        break;
    case L1:
        digitalWrite(LPWM1, pwm);
        break;
    case L2:
        digitalWrite(LPWM2, pwm);
        break;
    default:
        break;
    }
}
void StopMotor(int side) // Stop motor
{
    switch (side)
    {
    case R1:
        digitalWrite(RPWM1, LOW);
        break;
    case R2:
        digitalWrite(RPWM2, LOW);
        break;
    case L1:
        digitalWrite(LPWM1, LOW);
        break;
    case L2:
        digitalWrite(LPWM2, LOW);
        break;
    default:
        break;
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
void InitIRSensor(void) // Initialize IR sensors
{
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
}
void InitColorSensor(void) // Initialize color sensors
{
    // Actually, Color sensor is no need to initialize
}
void InitMotorControl(void) // Initialize motor settings (All Enable, All Stop)
{
    MotorActiveStatus(R1, ON);
    MotorActiveStatus(R2, ON);
    MotorActiveStatus(L1, ON);
    MotorActiveStatus(L2, ON);
    StopMotor(R1);
    StopMotor(R2);
    StopMotor(L1);
    StopMotor(L2);
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
    InitMotorControl();
    InitCamSerial(mySerial, baudrate);
}

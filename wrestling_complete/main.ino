#include "algorithm.hpp"
#include "function.hpp"
#include "motor.hpp"

void setup()
{
    SoftwareSerial mySerial(52, 50); // RX, TX
    Adafruit_TCS34725softi2c tcs1 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin1, SCLpin);
    Adafruit_TCS34725softi2c tcs2 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin2, SCLpin);
    Adafruit_TCS34725softi2c tcs3 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin3, SCLpin);
    Adafruit_TCS34725softi2c tcs4 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin4, SCLpin);

    initCamSerial(mySerial, 9600);
    initIRSensor();
    initColorSensor(tcs1, tcs2, tcs3, tcs4);
    InitMotor();
}

void loop()
{
    
}
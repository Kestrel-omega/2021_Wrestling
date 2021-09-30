#include <Wrestling_Header.h>

// Declare classes for color sensors
Adafruit_TCS34725softi2c tcs1 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin1, SCLpin);
Adafruit_TCS34725softi2c tcs2 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin2, SCLpin);
Adafruit_TCS34725softi2c tcs3 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin3, SCLpin);
Adafruit_TCS34725softi2c tcs4 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin4, SCLpin);
Color color[4];

char str[255];

void setup()
{
    InitColorSensor();
    Serial.begin(9600);
}

void loop()
{
    color[0] = ReadColorSensor(tcs1);
    color[1] = ReadColorSensor(tcs2);
    color[2] = ReadColorSensor(tcs3);
    color[3] = ReadColorSensor(tcs4);

    sprintf(str, "1: %f, %f, %f\n2: %f, %f, %f\n3: %f, %f, %f\n4: %f, %f, %f\n", color[0].red, color[0].green, color[0].blue,color[1].red, color[1].green, color[1].blue,color[2].red, color[2].green, color[2].blue,color[3].red, color[3].green, color[3].blue);

    Serial.print(str);

    delay(60);
}

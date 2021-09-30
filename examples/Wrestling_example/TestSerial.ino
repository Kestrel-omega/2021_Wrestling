#include "Wrestling_Header.h"

SoftwareSerial mySerial(RX1, TX1);
int x_value, y_value, size_value;

char str[63];

void setup()
{
    InitCamSerial(mySerial, 9600);
    // Serial.begin(9600);
}

void loop()
{
    ReadCamData(mySerial, x_value, y_value, size_value);

    sprintf(str, "x : %d, y : %d, size : %d\n", x_value, y_value, size_value);
    Serial.print(str);
}
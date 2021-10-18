#include <SoftwareSerial.h>

SoftwareSerial SSerial(19, 18);

void setup()
{
  Serial.begin(9600);
  SSerial.begin(9600);
}

void loop()
{
  if(SSerial.available())
  {
    
    Serial.write(SSerial.read());
  }
}

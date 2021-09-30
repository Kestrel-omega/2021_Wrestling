#include "Wrestling_Header.h"

void setup() {
  
void InitIRSensor();
float ReadIRSensor(int idx);
Serial.begin(9600);

}

void loop() {

Serial.print(ReadIRSensor(0));
Serial.print(ReadIRSensor(1));
Serial.print(ReadIRSensor(2));
Serial.print(ReadIRSensor(3));
  
}

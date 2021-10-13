#include "Wrestling_Header.h"

// Declare classes for color sensors
Adafruit_TCS34725softi2c tcs1 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin1, SCLpin);
Adafruit_TCS34725softi2c tcs2 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin2, SCLpin);
Adafruit_TCS34725softi2c tcs3 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin3, SCLpin);
Adafruit_TCS34725softi2c tcs4 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin4, SCLpin);
struct Color color[4];

//initialize IR, Color, Motordrive, Camera
void setup() 
{
  InitMotor();
  InitIRSensor();

  if(tcs1.begin() && tcs2.begin() && tcs3.begin() && tcs4.begin() )
    {
      Serial.println("Found sensor");
    } 
  else 
    {
      Serial.println("Found fail");
    }
   InitColorSensor();
   Serial.begin(9600);
   
}

void loop() 
{
  MotorActiveStatus(1); //Motor on!
  //주기적으로 받음
  color[0] = ReadColorSensor(tcs1);
  color[1] = ReadColorSensor(tcs2);
  color[2] = ReadColorSensor(tcs3);
  color[3] = ReadColorSensor(tcs4);


    if( Color_black()&& IR_safe()) // chage value red & blue
    {
      
      while(Cam_found())
     {
       analogWrite(R_PWM1,200);
       analogWrite(L_PWM2,200);
     }  
      if (Cam_found())
      {
        
        CAMMID = 320;
        x = CAMMID - CAM_X;

       while(pixel <000)
       {
        if( x <0)
         {
          analogWrite(R_PWM1,255*abs(a/320));
          analogWrite(R_PWM2,0);
         } 
         else if(x>0)
         {
          analogWrite(R_PWM1,0);
          analogWrite(R_PWM2,255*abs(a/320));
         } 
         else if(x=0)
         {
          analogWrite(R_PWM1,255*abs(a/320));
          analogWrite(R_PWM2,255*abs(a/320));
         }
       }          
      }
      
     }
    else if( Color_black()&& ReadIRSensor(1)<25)
    {
      while(ReadIRSensor(1)>=25)
      {
        analogWrite(R_PWM1,200);
        analogWrite(R_PWM2,100);
      }
    else if( Color_black()&& ReadIRSensor(2)<25)
    {
      while(ReadIRSensor(2)>=25)
      {
        analogWrite(R_PWM1,100);
        analogWrite(R_PWM2,200);
      }
    }
    else if( Color_black()&& ReadIRSensor(3)<25)
    {
      while(ReadIRSensor(3)>=25)
      {
        analogWrite(R_PWM1,200);
        analogWrite(R_PWM2,200);
      }

  
  
}

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


    if( Color_black()&& IR_safe() ) // chage value red & blue
    {
      
      while(Cam_found()== 0) // 캠발견할때까지 제자리회전
     {
       analogWrite(R_PWM1,200);
       analogWrite(L_PWM2,200);

       if(IR_safe() == 0)
       {
        break ;
        }
     }
    }  
    else if (Cam_found() == 1)  // 상대방 발견
    {
        
        CAMMID = 320;
        x = CAMMID - CAM_X;   // 상대방 x좌표 반환

       while(pixel <000)  // 상대방과 일정거리 가까워질 때까지
       {
        if( x <0)  // 상대방 우측에 있을때 우회전
         {
          analogWrite(R_PWM1,255*abs(a/320));
          analogWrite(R_PWM2,0);
         } 
         else if(x>0)  // 상대방 좌측에 있을때 좌회전
         {
          analogWrite(R_PWM1,0);
          analogWrite(R_PWM2,255*abs(a/320));
         } 
         else if(x=0) // 상대방 중간에 있을때 직진
         {
          analogWrite(R_PWM1,255*abs(a/320));
          analogWrite(R_PWM2,255*abs(a/320));
         }
         
         if(Color_left())
         {
          analogWrite(R_PWM1,200);
          analogWrite(R_PWM2,100); 
         }
         else if(Color_right())
         {
          analogWrite(R_PWM1,100);
          analogWrite(R_PWM2,200); 
         }
    
          
        }
        while(pixel >000 ) // 상대방과 일정거리 가까워지면 그동안
         {
          analogWrite(R_PWM1,250);
          analogWrite(R_PWM2,250);    // 최대출력 직진

          if( Cam_found() == True) // 상대방 가까이 있는지 확인
          {
            color[0] = ReadColorSensor(tcs1);
            color[1] = ReadColorSensor(tcs2);
            color[2] = ReadColorSensor(tcs3);
            color[3] = ReadColorSensor(tcs4);  // 컬러 확인
            
            if(ReadIRSensor(0)<=25 && color_red_front() )  // 컬러 프뤈ㅌ 뤠드 인식- 후진
            {
              analogWrite(L_PWM1,200);
              analogWrite(L_PWM2,200); 
              
              }
            else if(ReadIRSensor(0)<=25 && color_red_back()) //컬러 뿌액 뤠드 인식 - 전진
             {
              analogWrite(R_PWM1,200);
              analogWrite(R_PWM2,200); 
              
              }
           }
          }
      }
      
      
                 
      
      
     
    else if( Color_black()&& ReadIRSensor(1)<25)    // 검정에서 왼쪽 가까움
    {
      while(ReadIRSensor(1)>=25) // 왼쪽에서 멀어질때까지 우회전
      {
        analogWrite(R_PWM1,200);
        analogWrite(R_PWM2,100);
      }
      color[0] = ReadColorSensor(tcs1);
      color[1] = ReadColorSensor(tcs2);
      color[2] = ReadColorSensor(tcs3);
      color[3] = ReadColorSensor(tcs4);  // 컬러 확인
      
      if(Color_left())        // 컬러 왼쪽 인식이면 우회전
      {
       analogWrite(R_PWM1,200);
        analogWrite(R_PWM2,100); 
        }
      else if(Color_right())  // 컬러 오른쪽 인식이면 좌회전
      {
       analogWrite(R_PWM1,100);
        analogWrite(R_PWM2,200); 
        }
    }
    else if( Color_black()&& ReadIRSensor(2)<25)  // 검정에서 오른쪽 가까움
    {
      while(ReadIRSensor(2)>=25)
      {
        analogWrite(R_PWM1,100);
        analogWrite(R_PWM2,200);
      }
      
      color[0] = ReadColorSensor(tcs1);
      color[1] = ReadColorSensor(tcs2);
      color[2] = ReadColorSensor(tcs3);
      color[3] = ReadColorSensor(tcs4);
      
       if(Color_left())
      {
       analogWrite(R_PWM1,200);
        analogWrite(R_PWM2,100); 
        }
      else if(Color_right())
      {
       analogWrite(R_PWM1,100);
        analogWrite(R_PWM2,200); 
        }
    }
    else if( Color_black()&& ReadIRSensor(3)<25)  // 검정에서 뒤쪽 가까움
    {
      while(ReadIRSensor(3)>=25)
      {
        analogWrite(R_PWM1,200);
        analogWrite(R_PWM2,200);
      }

      color[0] = ReadColorSensor(tcs1);
      color[1] = ReadColorSensor(tcs2);
      color[2] = ReadColorSensor(tcs3);
      color[3] = ReadColorSensor(tcs4);
      
       if(Color_left())
      {
       analogWrite(R_PWM1,200);
        analogWrite(R_PWM2,100); 
        }
      else if(Color_right())
      {
       analogWrite(R_PWM1,100);
        analogWrite(R_PWM2,200); 
        }
    }
  
 return 0; 
}

#include "Wrestling_Header.h"
#define CAMMID 320
#define color0red 151
#define color0blue 125
#define color1red 176
#define color1blue 223
#define color2red 12
#define color2blue 10
#define color3red 22
#define color3blue 22
#define Cam_near 300


SoftwareSerial mySerial(52, 50); // RX, TX

int inString1;
int inString2;

// Declare classes for color sensors
Adafruit_TCS34725softi2c tcs1 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin1, SCLpin);
Adafruit_TCS34725softi2c tcs2 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin2, SCLpin);
Adafruit_TCS34725softi2c tcs3 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin3, SCLpin);
Adafruit_TCS34725softi2c tcs4 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X, SDApin4, SCLpin);
struct Color color[4];


/***********컬러색's 주기적으로 읽어***********/
void Read_color()
{
  color[0] = ReadColorSensor(tcs1);
  color[1] = ReadColorSensor(tcs2);
  color[2] = ReadColorSensor(tcs3);
  color[3] = ReadColorSensor(tcs4);
}

bool Color_black()
{
  return (color[0].red < color0red / 2 && color[0].blue < color0blue / 2 && color[1].red < color1red / 2 && color[1].blue < color1blue / 2 && color[2].red < color2red / 2 && color[2].blue < color2blue / 2 && color[3].red < color3red / 2 && color[3].blue < color3blue / 2);
}

bool Color_red_front()
{
  return (color[2].red > color2red || color[3].red > color3red);
}
bool Color_red_back()
{
  return color[0].red > color0red || color[1].red > color1red;
}
bool Color_left()
{
  return (color[1].red > color1red || color[1].blue > color1blue || color[3].red > color3red || color[3].blue > color3blue);
}
bool Color_right()
{
  return (color[0].red > color0red || color[0].blue > color0blue || color[2].red > color2red || color[2].blue > color2blue);
}
bool Color_blue_front()
{
  return color[2].blue > color2blue || color[3].blue > color3blue ;
}
/***********카메라's 체크해***********/
int ReadCamData()
{
  if (mySerial.available()) {

    String inString = mySerial.readStringUntil('\n');

    int index1 = inString.indexOf(',');
    int index2 = inString.length();
    inString1 = inString.substring(0, index1).toInt();
    inString2 = inString.substring(index1 + 1, index2).toInt();

    return 0;
  }
  else
  {
    return -1;
  }
}
bool Not_found()
{
  return inString1 == 0 && inString2 == 0 ;
}
void CAM_Serial()
{
  Serial.print("Cam :"); Serial.println(inString1);
}
/***********IR Sensor***********/
void IR_Serial()
{
  Serial.print("ir0 :"); Serial.print(ReadIRSensor(0)); Serial.print('\t');
  Serial.print("ir1 :"); Serial.print(ReadIRSensor(1)); Serial.print('\t');
  Serial.print("ir2 :"); Serial.print(ReadIRSensor(2)); Serial.print('\t');
  Serial.print("ir3 :"); Serial.print(ReadIRSensor(3)); Serial.print('\n');
}

//initialize IR, Color, Motordrive, Camera
void setup()
{
  InitMotor();
  InitIRSensor();
  MotorActiveStatus(1); //Motor on!
  delay(10);

  while (!Serial) {
    ;
  }

  mySerial.begin(2400);

  if (tcs1.begin() && tcs2.begin() && tcs3.begin() && tcs4.begin() )
  {
    Serial.println("Found sensor");
  }
  else
  {
    Serial.println("Found fail");
  }

  Serial.begin(9600);

}

void loop()
{
  Read_color();

  if (Not_found() == true)
  {
    if ( Color_black() && IR_safe() ) // chage value red & blue
    {
      while (1) // 캠발견할때까지 제자리회전
      {
        analogWrite(L_PWM1, 0);
        analogWrite(R_PWM2, 0);
        analogWrite(R_PWM1, 10);
        analogWrite(L_PWM2, 10);
        if ((inString1 > 0 && inString2 > 0) || IR_safe() == false)
        {
          break;
        }
      }
    }
    /****stop motor****/
    analogWrite(R_PWM1, 0);
    analogWrite(L_PWM2, 0);
    delay(10);
  }

  if (!Not_found() == false)  // 상대방 발견
  {

    int x = CAMMID - inString1;   // 상대방 x좌표 반환

    while ( inString2 < Cam_near) // 상대방과 가까운 위치에 있는 동안
    {
      if ( x < 0) // 상대방 우측에 있을때 우회전
      {
        analogWrite(R_PWM1, 255 * abs(x / 320));
        analogWrite(R_PWM2, 0);
        delay(50);
      }
      else if (x > 0) // 상대방 좌측에 있을때 좌회전
      {
        analogWrite(R_PWM1, 0);
        analogWrite(R_PWM2, 255 * abs(x / 320));
        delay(50);
      }

      analogWrite(R_PWM1, 0);
      analogWrite(L_PWM1, 0);
      analogWrite(R_PWM2, 0);
      analogWrite(L_PWM2, 0);
      delay(1);

      if (Color_left() == true)
      {
        analogWrite(R_PWM1, 200);
        analogWrite(R_PWM2, 100);
        delay(50);
      }
      else if (Color_right() == true)
      {
        analogWrite(R_PWM1, 100);
        analogWrite(R_PWM2, 200);
        delay(50);
      }
    }

    while ( inString2 > Cam_near ) // 상대방과 일정거리 가까워지면 그동안
    {

      Read_color();//read!read!read!
      analogWrite(R_PWM1, 200);
      analogWrite(R_PWM2, 200);
      if (ReadIRSensor(0) <= 25 && Color_red_front() == true ) // 컬러 프뤈ㅌ 뤠드 인식- 후진
      {
        analogWrite(R_PWM1, 0);
        analogWrite(R_PWM1, 0);
        delay(1);
        analogWrite(L_PWM1, 200);
        analogWrite(L_PWM2, 200);
        delay(500);
      }

    }
  }

  analogWrite(R_PWM1, 0);
  analogWrite(L_PWM1, 0);
  analogWrite(R_PWM2, 0);
  analogWrite(L_PWM2, 0);
  delay(1);
  if ( Color_black() && ReadIRSensor(1) < 25) // 검정에서 왼쪽 가까움
  {
    while (ReadIRSensor(1) >= 25) // 왼쪽에서 멀어질때까지 우회전
    {
      analogWrite(R_PWM1, 200);
      analogWrite(R_PWM2, 100);

      Read_color();//read!read!read!
      if (Color_blue_front() == true || Color_red_front == true) //우회전 도중 컬러 인식하는 경우
      {
        delay(10);

        analogWrite(L_PWM1, 200);
        analogWrite(L_PWM2, 200);
        delay(300);
      }
    }

    analogWrite(R_PWM1, 0);
    analogWrite(L_PWM1, 0);
    analogWrite(R_PWM2, 0);
    analogWrite(L_PWM2, 0);
    delay(1);
    /*
        Read_color();//read!read!read!

        if (Color_left()== true)       // 컬러 왼쪽 인식이면 우회전
        {
          analogWrite(R_PWM1, 200);
          analogWrite(R_PWM2, 100);
          delay(50);
        }
        else if (Color_right() == true) // 컬러 오른쪽 인식이면 좌회전
        {
          analogWrite(R_PWM1, 100);
          analogWrite(R_PWM2, 200);
        }
    */
  }
  else if ( Color_black() && ReadIRSensor(2) < 25) // 검정에서 오른쪽 가까움
  {
    while (ReadIRSensor(2) >= 25)
    {
      analogWrite(R_PWM1, 100);
      analogWrite(R_PWM2, 200);

      Read_color();//read!read!read!
      if (Color_blue_front() == true || Color_red_front == true) //좌회전 도중 컬러 인식하는 경우
      {
        delay(10);

        analogWrite(L_PWM1, 200);
        analogWrite(L_PWM2, 200);
        delay(300);
      }
    }
  }
  else if ( Color_black() && ReadIRSensor(3) < 25) // 검정에서 뒤쪽 가까움
  {
    while (ReadIRSensor(3) >= 25)
    {
      analogWrite(R_PWM1, 200);
      analogWrite(R_PWM2, 200);

      Read_color();//read!read!read!
      if (Color_blue_front() == true || Color_red_front == true) //직진 도중 컬러 인식하는 경우
      {
        delay(10);

        analogWrite(L_PWM1, 200);
        analogWrite(L_PWM2, 200);
        delay(300);
      }

    }
  }
  return 0;
}
/***********loop finish***********/

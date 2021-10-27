#include "Wrestling_Header.h"
#define CAMMID 320
#define color0red 63
#define color0blue 110
#define color1red 70
#define color1blue 115
#define color2red 65
#define color2blue 90
#define color3red 53
#define color3blue 100
#define Cam_near 300

#define CAMRANGE 30

#define RIGHT 40
#define MID 41
#define LEFT 42
#define NONE 43

#define IR_near 50

SoftwareSerial mySerial(52, 50); // RX, TX

int x_data;
int size_data;

// Declare classes for color sensors
Adafruit_TCS34725softi2c tcs1 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_4X, SDApin1, SCLpin);
Adafruit_TCS34725softi2c tcs2 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_4X, SDApin2, SCLpin);
Adafruit_TCS34725softi2c tcs3 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_4X, SDApin3, SCLpin);
Adafruit_TCS34725softi2c tcs4 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_4X, SDApin4, SCLpin);
struct Color color[4];

int Cam_direction(int x_data)
{
  int left_thres = CAMMID - CAMRANGE;
  int right_thres = CAMMID + CAMRANGE;

  if (x_data < left_thres && x_data > 0)
    return LEFT;
  else if (x_data > right_thres)
    return RIGHT;
  else if (x_data <= 0)
    return NONE;
  else
    return MID;
}
/***********컬러색's 주기적으로 읽어***********/
void Read_color()
{
  color[0] = ReadColorSensor(tcs1);
  color[1] = ReadColorSensor(tcs2);
  color[2] = ReadColorSensor(tcs3);
  color[3] = ReadColorSensor(tcs4);

  for (int i = 0; i < 4; i++)
  {
    Serial.print(i);
    Serial.print(".R : ");
    Serial.print(color[i].red);
    Serial.print("\t");
    Serial.print(i);
    Serial.print(".B : ");
    Serial.println(color[i].blue);
  }
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
  return color[2].blue > color2blue || color[3].blue > color3blue;
}
/***********카메라's 체크해***********/
int ReadCamData()
{
  while (!mySerial.available())
  {
  }
  String inString = mySerial.readStringUntil('\n');

  // Serial.println(inString);
  // char checksum = inString[0];
  // Serial.print("checksum : ");
  // Serial.println(checksum);
  int index1 = inString.indexOf(',');
  int index2 = inString.length();
  // Serial.print("index1 : ");
  // Serial.print(index1);
  // Serial.print("\tindex2 : ");
  // Serial.println(index2);
  if (index1 == 3 && index2 == 7)
  {
    x_data = inString.substring(0, index1).toInt();
    size_data = inString.substring(index1 + 1, index2).toInt();
  }

  Serial.print("Cam - x : ");
  Serial.print(x_data);
  Serial.print(", size : ");
  Serial.println(size_data);
  return 0;
}
bool Not_found()
{
  return x_data == 0 && size_data == 0;
}
void CAM_Serial()
{
  Serial.print("Cam : ");
  Serial.println(x_data);
  delay(50);
}
/***********IR Sensor***********/
void IR_Serial()
{
  Serial.print("ir0 :");
  Serial.print(ReadIRSensor(0));
  Serial.print('\t');
  Serial.print("ir1 :");
  Serial.print(ReadIRSensor(1));
  Serial.print('\t');
  Serial.print("ir2 :");
  Serial.print(ReadIRSensor(2));
  Serial.print('\t');
  Serial.print("ir3 :");
  Serial.print(ReadIRSensor(3));
  Serial.print('\n');
}

//initialize IR, Color, Motordrive, Camera
void setup()
{
  InitMotor();
  InitIRSensor();
  MotorActiveStatus(1); //Motor on!
  delay(10);

  while (!Serial)
  {
    ;
  }

  mySerial.begin(2400);

  if (tcs1.begin() && tcs2.begin() && tcs3.begin() && tcs4.begin())
  {
    Serial.println("Found sensor");
  }
  else
  {
    Serial.println("Found fail");
  }

  Serial.begin(9600);

  Serial.println("Start");
}

void loop()
{
  ReadCamData();
  Read_color();
  IR_Serial();
  Serial.print("\r\n\r\n");
  if (Not_found() == true)
  {
    if (Color_black() && IR_safe()) // chage value red & blue
    {
      Serial.println("Finding Enermy...");
      while (1) // 캠발견할때까지 제자리회전
      {
        ReadCamData();
        analogWrite(PWM_LB, 0);
        analogWrite(PWM_RF, 0);
        analogWrite(PWM_LF, 20);
        analogWrite(PWM_RB, 20);
        if ((x_data > 0 && size_data > 0) || IR_safe() == false)
        {
          break;
        }
      }
    }
    /****stop motor****/
    Serial.println("Something Found!");
    StopMotor();
  }
  else if (Not_found() == false) // 상대방 발견
  {
    ReadCamData();
    CAM_Serial();
    Serial.println("Enermy Found!");
    int x = CAMMID - x_data; // 상대방 x좌표 반환

    while (size_data < Cam_near && Cam_direction(x_data) != NONE) // 상대방과 먼 위치에 있는 동안
    {
      Serial.print("Enermy is far from us! : ");
      ReadCamData();
      CAM_Serial();

      switch (Cam_direction(x_data))
      {
      case LEFT:
      {
        Serial.println("LEFT");
        analogWrite(PWM_RB, 0);
        analogWrite(PWM_LF, 0);
        analogWrite(PWM_RF, 50);
        analogWrite(PWM_LB, 50);
        break;
      }
      case RIGHT:
      {
        Serial.println("RIGHT");
        analogWrite(PWM_RF, 0);
        analogWrite(PWM_LB, 0);
        analogWrite(PWM_LF, 50);
        analogWrite(PWM_RB, 50);
        break;
      }
      case MID:
      {
        Serial.println("MID");
        analogWrite(PWM_LB, 0);
        analogWrite(PWM_RB, 0);
        analogWrite(PWM_LF, 100);
        analogWrite(PWM_RF, 100);
        break;
      }
      default:
      {
        break;
      }
      }

      if (Color_left() == true)
      {
        analogWrite(PWM_LB, 0);
        analogWrite(PWM_RB, 0);
        analogWrite(PWM_LF, 70);
        analogWrite(PWM_RF, 50);

        ;
      }
      else if (Color_right() == true)
      {
        analogWrite(PWM_LB, 0);
        analogWrite(PWM_RB, 0);
        analogWrite(PWM_LF, 50);
        analogWrite(PWM_RF, 70);
      }

      delay(1);
    }

    while (size_data > Cam_near) // 상대방과 일정거리 가까워지면 그동안
    {
      Serial.print("Enermy is near from us! : ");
      ReadCamData();
      CAM_Serial();
      int red_count = 0;
      int x = CAMMID - x_data; // 상대방 x좌표 반환
      Read_color();            //read!read!read!
      analogWrite(PWM_LB, 0);
      analogWrite(PWM_RB, 0);
      analogWrite(PWM_LF, 200);
      analogWrite(PWM_RF, 200);

      if (ReadIRSensor(0) <= IR_near && Color_red_front() == true) // 컬러 프뤈ㅌ 뤠드 인식- 후진
      {
        analogWrite(PWM_LF, 0);
        analogWrite(PWM_RF, 0);
        analogWrite(PWM_LB, 200);
        analogWrite(PWM_RB, 200);
        delay(50);
        red_count++;

        if (red_count == 3)
        {
          analogWrite(PWM_RF, 0);
          analogWrite(PWM_LB, 0);
          analogWrite(PWM_LF, 200);
          analogWrite(PWM_RB, 200);
          red_count = 0;
        }
      }

      delay(1);
    }
  }

  if (Color_black() && ReadIRSensor(1) < IR_near) // 검정에서 왼쪽 가까움
  {
    Serial.println("Left Wall");
    while (ReadIRSensor(1) < IR_near) // 왼쪽에서 멀어질때까지 우회전
    {
      analogWrite(PWM_LB, 0);
      analogWrite(PWM_RB, 0);
      analogWrite(PWM_LF, 50);
      analogWrite(PWM_RF, 20);

      IR_Serial();
      Read_color();                                              //read!read!read!
      if (Color_blue_front() == true || Color_red_front == true) //우회전 도중 컬러 인식하는 경우
      {
        analogWrite(PWM_LF, 0);
        analogWrite(PWM_RF, 0);
        analogWrite(PWM_LB, 50);
        analogWrite(PWM_RB, 50);
      }
    }
  }
  else if (Color_black() && ReadIRSensor(2) < IR_near) // 검정에서 오른쪽 가까움
  {
    Serial.println("Right Wall");
    while (ReadIRSensor(2) < IR_near)
    {
      analogWrite(PWM_LB, 0);
      analogWrite(PWM_RB, 0);
      analogWrite(PWM_LF, 20);
      analogWrite(PWM_RF, 50);

      IR_Serial();
      Read_color();                                              //read!read!read!
      if (Color_blue_front() == true || Color_red_front == true) //좌회전 도중 컬러 인식하는 경우
      {
        analogWrite(PWM_LF, 0);
        analogWrite(PWM_RF, 0);
        analogWrite(PWM_LB, 50);
        analogWrite(PWM_RB, 50);
      }
    }
  }
  else if (Color_black() && ReadIRSensor(3) < IR_near) // 검정에서 뒤쪽 가까움
  {
    Serial.println("Back Wall");
    while (ReadIRSensor(3) < IR_near)
    {
      analogWrite(PWM_LB, 0);
      analogWrite(PWM_RB, 0);
      analogWrite(PWM_LF, 50);
      analogWrite(PWM_RF, 50);
    }
  }
  else
  {
    Serial.println("No Black Floor");
    StopMotor();
  }
}
/***********loop finish***********/

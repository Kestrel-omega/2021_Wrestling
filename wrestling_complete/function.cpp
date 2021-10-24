#include "functions.hpp"

/* Initialize Functions */

// Initialize camera sensor
void initCamSerial(struct SoftwareSerial mySerial, int baudrate) // Initialize jetson - arduino serial communication settings
{
	Serial.begin(baudrate);
	mySerial.begin(baudrate);
}

// Initialize IR sensors
void initIRSensor(void)
{
	pinMode(IR1, INPUT);
	pinMode(IR2, INPUT);
	pinMode(IR3, INPUT);
	pinMode(IR4, INPUT);

    Serial.println("Initialize IR Sensors Done");
}

// Initialize Color sensors
void initColorSensor(struct Adafruit_TCS34725softi2c tcs1, struct Adafruit_TCS34725softi2c tcs2, struct Adafruit_TCS34725softi2c tcs3, struct Adafruit_TCS34725softi2c tcs4)
{ 
  if (tcs1.begin() && tcs2.begin() && tcs3.begin() && tcs4.begin() )
  {
    Serial.println("Initialize Color Sensors");
  }
  else
  {
    Serial.println("Failed : Color Sensors");
    exit(-1);
  }
}

// input : SoftwareSerial class "mySerial"
// output : 1 bit near status (0 : far, 1 : near) + 2 bit direction status (00 : none, 01 : right, 10 : left, 11 : center)
int readCamData(struct SoftwareSerial mySerial)
{
    if (mySerial.available()) // parse camera data
    {
        String inString = mySerial.readStringUntil('\n');

        int index_x = inString.indexOf(',');
        int index_size = inString.length();
        int x_data = inString.substring(0, index_x).toInt();
        int size_data = inString.substring(index_x + 1, index_size).toInt();
    }
    else
    {
        return -1;
    }

    int cam_x_status = 0b00;   // 00 : none, 01 : right, 10 : left, 11 : center
    int cam_size_status = 0b0; // 0 : far enough, 1 : near

    int cam_center_upper = CAM_MID + CAM_RANGE;
    int cam_center_lower = CAM_MID - CAM_RANGE;

    int cam_status;
    if (x_data < cam_center_lower)
        cam_x_status = 0b01;
    else if (x_data > cam_center_upper)
        cam_x_status = 0b10;
    else if (x_data == 0)
        cam_x_status = 0b00;
    else
        cam_x_status = 0b11;

    if (size_data > CAM_NEAR)
        cam_size_status = 1 * 4;

    cam_status = cam_size_status + cam_x_status;

    return cam_status;
}

// input : Adafruit_TCS34725softi2c class tcs1~4
// output : 2 bit color status x 4 (00 : black, 01 : red, 10 : blue, 11 : error)
int readColorSensor(struct Adafruit_TCS34725softi2c tcs1, struct Adafruit_TCS34725softi2c tcs2, struct Adafruit_TCS34725softi2c tcs3, struct Adafruit_TCS34725softi2c tcs4)
{
    int color_status = 0b00000000; // status (00 : black, 01 : red, 10 : blue, 11 : error)
    uint16_t clear[4], red[4], green[4], blue[4];
    uint32_t sum = clear[4];

    tcs1.setInterrupt(false);
    tcs2.setInterrupt(false);
    tcs3.setInterrupt(false);
    tcs4.setInterrupt(false);

    struct Adafruit_TCS34725softi2c tcs_target;

    delay(60);

    for (int i = 1; i <= 4; i++)
    {
        int status = 0b00000000;
        int red_threshold, blue_threshold;
        switch (i)
        {
        case 1:
            tcs_target = tcs1;
            red_threshold = COLOR_1_RED;
            blue_threshold = COLOR_1_BLUE;
            break;
        case 2:
            tcs_target = tcs2;
            red_threshold = COLOR_2_RED;
            blue_threshold = COLOR_2_BLUE;
            break;
        case 3:
            tcs_target = tcs3;
            red_threshold = COLOR_3_RED;
            blue_threshold = COLOR_3_BLUE;
            break;
        case 4:
            tcs_target = tcs4;
            red_threshold = COLOR_4_RED;
            blue_threshold = COLOR_4_BLUE;
            break;
        default:;
        }
        tcs_target.getRawData(&red[i], &green[i], &blue[i], &clear[i]);
        tcs_target.setInterrupt(true);

        if (red[i] > red_threshold)
            status += 1;
        if (blue[i] > blue_threshold)
            status += 2;

        color_status += status * pow(2, (i - 1) * 2);
    }
    return color_status;
}

// input : none
// output : i bit near status x 4 (0 : far, 1 : near))
int readIRData(void)
{
    int ir_status = 0b00;

    float sensor_value[4];
    float dist[4];

    sensor_value[0] = analogRead(IR1);
    sensor_value[1] = analogRead(IR2);
    sensor_value[2] = analogRead(IR3);
    sensor_value[3] = analogRead(IR4);

    for (int i = 0; i < 4; i++)
    {
        dist[i] = 10650.08 * pow(sensor_value[i], -0.935) - 10;
        if (dist[i] > IR_DIST)
        {
            ir_status += 1 * pow(2, i);
        }
    }
    return ir_status;
}


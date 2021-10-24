#pragma once
#ifndef __FUNCTION_HPP__
#define __FUNCTION_HPP__

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <String.h>
#include <stdio.h>
#include "Adafruit_TCS34725softi2c.h"

// get algorithm with status flags

// camera threshold value
#define CAM_MID 320
#define CAM_RANGE 10
#define CAM_NEAR 300

// color sensor threshold value
#define COLOR_1_RED 151
#define COLOR_1_BLUE 125
#define COLOR_2_RED 176
#define COLOR_2_BLUE 223
#define COLOR_3_RED 12
#define COLOR_3_BLUE 10
#define COLOR_4_RED 22
#define COLOR_4_BLUE 20

// IR dist sensor thresholld value
#define IR_DIST 25

// Initialize camera sensor & serial begin
void initCamSerial(struct SoftwareSerial mySerial, int baudrate); // Initialize jetson - arduino serial communication settings
// Initialize IR sensors
void initIRSensor(void);
// Initialize Color sensors
void initColorSensor(struct Adafruit_TCS34725softi2c tcs1, struct Adafruit_TCS34725softi2c tcs2, struct Adafruit_TCS34725softi2c tcs3, struct Adafruit_TCS34725softi2c tcs4);
// input : SoftwareSerial class "mySerial"
// output : 1 bit near status (0 : far, 1 : near) + 2 bit direction status (00 : none, 01 : right, 10 : left, 11 : center)
int readCamData(struct SoftwareSerial mySerial);
// input : Adafruit_TCS34725softi2c class tcs1~4
// output : 2 bit color status x 4 (00 : black, 01 : red, 10 : blue, 11 : error)
int readColorSensor(struct Adafruit_TCS34725softi2c tcs1, struct Adafruit_TCS34725softi2c tcs2, struct Adafruit_TCS34725softi2c tcs3, struct Adafruit_TCS34725softi2c tcs4);
// input : none
// output : i bit near status x 4 (0 : far, 1 : near))
int readIRData(void);

#endif
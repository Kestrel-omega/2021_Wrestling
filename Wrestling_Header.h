#pragma once
#ifndef __WRESTLING_HEADER_H__
#define __WRESTLING_HEADER_H__

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <String.h>
#include <stdio.h>
#include "Adafruit_TCS34725softi2c.h"

// Pinmap setting for arduino mega 2560
#define IR1 A0
#define IR2 A2
#define IR3 A4
#define IR4 A6
#define SDApin1 2
#define SDApin2 3
#define SDApin3 4
#define SDApin4 5
#define L_EN1 13
#define R_EN1 12
#define L_PWM1 11 //back
#define R_PWM1 10 //forward
#define L_EN2 9
#define R_EN2 8
#define L_PWM2 7  // forward
#define R_PWM2 6 //back
#define TX1 18
#define RX1 19
#define SCLpin 20

// Macro of motor
#define ON true
#define OFF false
#define R1 101
#define R2 102
#define L1 111
#define L2 112

// Declare color class
struct Color
{
    float red;
    float green;
    float blue;
};

// Initialize
void InitIRSensor();        // Initialize IR sensors
void InitColorSensor();     // Initialize color sensors
void InitMotor();    // Initialize motor settings
void InitCamSerial(struct SoftwareSerial mySerial, int baudrate);       // Initialize jetson - arduino serial communication settings
void InitBot(struct SoftwareSerial mySerial, int baudrate);             // Initialize all of things

// IR sensor library
void IR_safe(); // IR 2,3,4 far from 25cm
float ReadIRSensor(int idx);    // Read IR sensor to get a distance from obstacles (idx : 0~3)

// Color sensor library
void Color_black(); //color0,1,2,3 all black
void Color_red_front(); //color 0 or 1 is red
void Color_red_back(); // color 2 or 3 is red
void Color_left();
void Color_right();
struct Color ReadColorSensor(struct Adafruit_TCS34725softi2c tcs); // Read color sensor in r, g, b value

// Motor control library
void StopMotor(); // shut down all motor
void MotorActiveStatus(int a); // Set motor turn on/off, a==1: turn on, a==0 : turn off

// Camera serial library
void ReadCamData(struct SoftwareSerial mySerial, int &x_value, int &y_value, int &size_value);          // Read camera data from jetson nano

#endif

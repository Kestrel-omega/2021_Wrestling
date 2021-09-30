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
#define IR2 A1
#define IR3 A2
#define IR4 A3
#define SDApin1 2
#define SDApin2 3
#define SDApin3 4
#define SDApin4 5
#define RPWM1 6
#define R_EN1 7
#define LPWM1 8
#define L_EN1 9
#define RPWM2 10
#define R_EN2 11
#define LPWM2 12
#define L_EN2 13
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
void InitIRSensor(void);        // Initialize IR sensors
void InitColorSensor(void);     // Initialize color sensors
void InitMotorControl(void);    // Initialize motor settings
void InitCamSerial(struct SoftwareSerial mySerial, int baudrate);       // Initialize jetson - arduino serial communication settings
void InitBot(struct SoftwareSerial mySerial, int baudrate);             // Initialize all of things

// IR sensor library
float ReadIRSensor(int idx);    // Read IR sensor to get a distance from obstacles (idx : 0~3)

// Color sensor library
void ReadColorSensor(struct Adafruit_TCS34725softi2c tcs, struct Color color); // Read color sensor in r, g, b value

// Motor control library
void SetPWMfrequency(int freq);                     // Set motor PWM frequency
void MotorActiveStatus(int side, bool status);   // Set motor turn on/off
void SetMotorSpeed(int side,byte pwm);              // Set motor PWM
void StopMotor(int side);                           // Stop motor

// Camera serial library
void ReadCamData(struct SoftwareSerial mySerial, int &x_value, int &y_value, int &size_value);          // Read camera data from jetson nano

#endif
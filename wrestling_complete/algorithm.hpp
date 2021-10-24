#pragma once
#ifndef __ALGORITHM_HPP__
#define __ALGORITHM_HPP__

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
#define L_PWM2 6  // forward
#define R_PWM2 7 //back
#define TX1 18
#define RX1 19
#define SCLpin 21

// Macro of motor
#define ON true
#define OFF false
#define R1 101
#define R2 102
#define L1 111
#define L2 112



#endif
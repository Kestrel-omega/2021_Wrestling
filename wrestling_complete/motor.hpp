#pragma once

#ifndef __MOTOR_HPP__
#define __MOTOR_HPP__

#define ON true
#define OFF false
#define R1 101
#define R2 102
#define L1 111
#define L2 112

void InitMotor();
void StopMotor(); // shut down all motor
void MotorActiveStatus(int a); // Set motor turn on/off

#endif
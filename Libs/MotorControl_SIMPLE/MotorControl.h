/*==================================================== CUBESAT CONTROL SYSTEM ====================================================*/
/***
 * Lucas Gabriel Ferreira Lima (LucasGabrielfl0) 
 * Electrical Engineering Department (DEE)
 * Federal University of Pernambuco (UFPE)
 
 * Methods to control a DC Motor using a Hbridge
 * this system was designed for a LN298N
 ***/
#ifndef _MOTOR_CONTROL_H_
#define _MOTOR_CONTROL_H_
#include <Arduino.h>

/* PWM Config */
#define PWM_FREQ        1000    // PWM frequency in Hz
#define PWM_DC_RES      8       // Duty Cycle Resolution
#define PWM_CHANEL      0       // Chanel in the esp32 (0 to 15)

/* Motor Pins */
// Direction Control
#define IN1_PIN         2       // PIN for Switchs 1 and 4 (Hbridge motor 1)
#define IN2_PIN         4       // PIN for Switchs 2 and 3 (Hbridge motor 1)
#define IN3_PIN         16      // PIN for Switchs 1 and 4 (Hbridge motor 2)
#define IN4_PIN         17      // PIN for Switchs 2 and 3 (Hbridge motor 2)

// Velocity Control
#define ENA_PIN         15      // Enable PIN for motor 1 [PWM PIN]
#define ENB_PIN         5       // Enable PIN for motor 2 [PWM PIN]


/* Methods */
void setFoward();           //
void setReverse();          //
void shutdown();            //
void setup();
void setPWM(float DutyC);   // Set PWM at 



#endif
/*==================================================== CUBESAT CONTROL SYSTEM ====================================================*/
/***
 * Lucas Gabriel Ferreira Lima (Git: LucasGabrielfl0)
 * Electrical Engineering Department (DEE)
 * Federal University of Pernambuco (UFPE)
 
 * Methods to control a DC Motor using a Hbridge
 * this system was designed for a LN298N
 ***/
#include "MotorControl.h"
#include <Arduino.h>


MotorControl::MotorControl(uint8_t IN1_pin_,uint8_t IN2_pin_,uint8_t EN_pin_ )
:IN1_Pin{IN1_pin_} , IN2_Pin{IN2_pin_} , EN_Pin{EN_pin_} {};

// MotorControl::MotorControl(){
//     setup(PWM_FREQ, PWM_DC_RES, PWM_CHANEL);
// };


void MotorControl::setFoward(){
    delay(100);
    digitalWrite(IN1_Pin, HIGH);
    digitalWrite(IN2_Pin, LOW);
}

void MotorControl::setReverse(){
    delay(100);
    digitalWrite(IN1_Pin, LOW);
    digitalWrite(IN2_Pin, HIGH);
}

void MotorControl::shutdown(){
    delay(100);
    digitalWrite(IN1_Pin, LOW);
    digitalWrite(IN2_Pin, LOW);
}

MotorControl::MotorControl(){}


void MotorControl::setup(){
    // Hbridge Setup, 1 Motor
    pinMode(IN1_Pin, OUTPUT);   // 
    pinMode(IN2_Pin, OUTPUT);   //

    // Board's PWM set up
    pinMode(EN_Pin, OUTPUT);                        // PWM pin mode as Output
    ledcSetup(PWM_CHANEL,PWM_FREQ,PWM_DC_RES);      // Chanel, Frequency, and resolution
    ledcAttachPin(EN_Pin, PWM_CHANEL);              // Pin
}

void MotorControl::setPWM(float DutyC){
    uint8_t Dc_8b= uint8_t(abs(DutyC)*255);              // Assuming RES = 8bit
    delay(100);
    
    // Negative DC: Reverse, Positive DC: Foward
    if(DutyC<0){
        // SetReverse();
        ledcWrite(PWM_CHANEL, 255);
    } 
    else{
        setFoward();
        ledcWrite(PWM_CHANEL, DutyC);
    }
}


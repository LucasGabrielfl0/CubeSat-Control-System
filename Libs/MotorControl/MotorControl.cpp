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




void MotorControl::SetFoward(){
    delay(100);
    digitalWrite(IN1_Pin, HIGH);
    digitalWrite(IN2_Pin, LOW);
}
void MotorControl::SetReverse(){
    delay(100);
    digitalWrite(IN1_Pin, LOW);
    digitalWrite(IN2_Pin, HIGH);
}

void MotorControl::Shutdown(){
    delay(100);
    digitalWrite(IN1_Pin, LOW);
    digitalWrite(IN2_Pin, LOW);
}

void MotorControl::SetPWM(float DutyC){
    delay(100);
    // Negative Dc: Reverse
    if(DutyC<0){
        // SetReverse();
        DutyC= abs(DutyC);
        ledcWrite(EN_Pin, DutyC);
    } 
    else{
        SetFoward();
        ledcWrite(EN_Pin, DutyC);
    }
}




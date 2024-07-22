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


// MotorControl::MotorControl(){
//     setup(PWM_FREQ, PWM_DC_RES, PWM_CHANEL);
// };


void setFoward(){
    delay(100);
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, LOW);
}

void setReverse(){
    delay(100);
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, HIGH);
}

void shutdown(){
    delay(100);
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, LOW);
}

void setup(){
    // Hbridge Setup, 1 Motor
    pinMode(IN1_PIN, OUTPUT);   // 
    pinMode(IN2_PIN, OUTPUT);   //

    // Board's PWM set up
    pinMode(ENA_PIN, OUTPUT);                        // PWM pin mode as Output
    ledcSetup(PWM_CHANEL,PWM_FREQ,PWM_DC_RES);      // Chanel, Frequency, and resolution
    ledcAttachPin(ENA_PIN, PWM_CHANEL);              // Pin
}

void setPWM(float DutyC){
    uint8_t Dc_8b= uint8_t(abs(DutyC)*255);              // Assuming RES = 8bit
    delay(100);
    
    // Negative DC: Reverse, Positive DC: Foward
    if(DutyC<0){
        // SetReverse();
        ledcWrite(PWM_CHANEL, 255);
    } 
    else{
        setFoward();
        ledcWrite(PWM_CHANEL, Dc_8b);
    }
}


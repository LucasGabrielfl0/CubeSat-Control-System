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

// Config
#define PWM_CHANEL      1   // Chanel in the esp32 (0 to 15)
#define PWM_FREQ        1   // PWM frequency in Hz
#define PWM_DC_RES       1   // Duty Cycle Resolution

/* Motor Pins */
// Direction
#define IN1_PIN         1   // PIN for Switchs 1 and 4 Motor 1 (Hbridge 1)
#define IN2_PIN         1   // PIN for Switchs 2 and 3 Motor 2 (Hbridge 1)
#define IN3_PIN         1   // PIN for Switchs 1 and 4 Motor 2 (Hbridge 2)
#define IN4_PIN         1   // PIN for Switchs 2 and 3 Motor 2 (Hbridge 2)

// Speed
#define ENA_PIN         1   // Enable PIN for motor 1 [PWM PIN]


class MotorControl {
    /* Atributes */
    uint8_t IN1_Pin{IN1_PIN};        //
    uint8_t IN2_Pin{IN2_PIN};        //
    uint8_t EN_Pin{ENA_PIN};         // [PWM]

    /* Methods */
    void SetFoward();           //
    void SetReverse();          //
    void Shutdown();            //
    void Setup(uint32_t freq_hz, uint8_t resolution, uint8_t channel);
    void SetPWM(float DutyC);   // Set PWM at 

    /* Constructors */
    MotorControl(uint8_t IN1_pin,uint8_t IN2_pin,uint8_t EN_pin );
    MotorControl();
};

MotorControl::MotorControl(uint8_t IN1_pin_,uint8_t IN2_pin_,uint8_t EN_pin_ )
:IN1_Pin{IN1_pin_} , IN2_Pin{IN2_pin_} , EN_Pin{EN_pin_} {};

void MotorControl::Setup(uint32_t freq_hz, uint8_t resolution, uint8_t channel){
    // Hbridge Setup, 1 Motor
    pinMode(IN1_Pin, OUTPUT);   // 
    pinMode(IN2_Pin, OUTPUT);   //
    pinMode(EN_Pin, OUTPUT);    //

    // Board's PWM set up
    // ledcAttachChannel(EN_Pin, freq_hz, resolution, channel);
}



#endif
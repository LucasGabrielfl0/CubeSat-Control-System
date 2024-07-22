/*==================================================== CUBESAT CONTROL SYSTEM ====================================================*/
/***
 * Lucas Gabriel Ferreira Lima
 * Electrical Engineering Department (DEE)
 * Federal University of Pernambuco (UFPE)
 
 * This file contains the control system for a 1 axys attitude control of a cubesat 
 * this system was designed for a ESP32 microcontroller
 ***/

#ifndef _CONTROL_SYSTEM_H_
#define _CONTROL_SYSTEM_H_
#include <Arduino.h>

/*===================================== CONTROL PARAMETERS =====================================*/
// Control Signal
#define DC_MAX      0.5     // Maximum Dutycycle value
#define DC_MIN      0       // Minimum Dutycycle value

// Gains
#define KP	        10     	// Proporcional Gain
#define KI          10     	// Integral Gain
#define KD          10    	// Derivative Gain
#define TF          1		// Time constant of the Filter in the derivative gain 

#define TS          1e-3	// Sampling time in sec


class ControlSystem {
    private:
    // Atributes:
    float Kp{KP};           // Proporcional Gain
    float Ki{KI};           // Integral Gain
    float Kd{KD};           // Derivative Gain
    float Tf{TF};           // Filter in the Derivative term
    double Ts{TS};         // Sample Time in sec

    float Angle_ref{0};     // Reference Angle
    float error_c;          // Current error    
    float error_prev;       // Previous error

    public:
    // Methods:
    void set_Gains(float Kp, float Ki, float Kd, float Tf);
    float control();
    float control(float angle, float setpoint);
    void OpenLoopStep(float Dc_pwm);                // Apply Step directly into the plant (Open Loop)
    void ClosedLoopStep(float angle);               // Apply Step on the closed Loop (set reference)


    // Constructors:
    ControlSystem(float _kp, float _ki, float _kd, float _tf, double _ts);
    ControlSystem();
};


#endif

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
#define DC_MAX          0.5     // Maximum Dutycycle value
#define DC_MIN         -0.5     // Minimum Dutycycle value
#define MAX_ERROR       0.4     //

// Gains
#define KP	        0.016     	    // Proporcional Gain
#define KI          0.00     	    // Integral Gain
#define KD          0.095    	        // Derivative Gain
#define TF          0.01		    // Time constant of the Filter in the derivative gain 

#define TS          1e-3	        // Sampling time in sec


class ControlSystem {
    public:
    // Atributes:
    float Kp{KP};               // Proporcional Gain
    float Ki{KI};               // Integral Gain
    float Kd{KD};               // Derivative Gain
    float Tf{TF};               // Filter in the Derivative term
    double Ts{TS};              // Sample Time in sec
    bool shutdown{true};       //

    float uk[3]{0,0,0};         // Control Signal (output)
    float ek[3]{0,0,0};         // Error Signal (Input)

    float N0{0},N1{0},N2{0};    // Coefficients for transfer functions Numerator
    float D0{0},D1{0},D2{0};    // Coefficients for tranfer functions Denominator

    public:
    // Methods:
    void set_Gains(float Kp, float Ki, float Kd, float Tf);
    void CalcDiff();                                // Calculate differential equation based on control parameters
    float control(float angle_c, int setpoint_c);
    void ClosedLoopStep(float angle);               // Apply Step on the closed Loop (set reference)


    // Constructors:
    ControlSystem(float _kp, float _ki, float _kd, float _tf, double _ts);
    ControlSystem();
};


#endif

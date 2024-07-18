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
struct PidStruct{
    float Kp{1};
    float Ki{0};
    float Kp{0};
    
    float Tf{0};
};

class ControlSystem {
    private:
    // Atributes:
    float Kp{1};            // Proporcional Gain
    float Ki{0};            // Integral Gain
    float Kd{0};            // Derivative Gain
    float Tf{0};            // Filter in the Derivative term
    
    float Ts;               // Sample Time in sec

    float Angle_ref{0};     // Reference Angle
    float error_c;          // Current error    
    float error_prev;       // Previous error


    public:
    // Methods:
    void set_Gains(float Kp, float Ki, float Kd, float Tf);
    void get_Gains();
    float control();
    void OpenLoopStep(float Dc_pwm);                // Apply Step directly into the plant (Open Loop)
    void ClosedLoopStep(float angle);               // Apply Step on the closed Loop (set reference)


    // Constructors:
    ControlSystem(float _kp, float _ki, float _kd, float _tf, float _ts);

};


#endif

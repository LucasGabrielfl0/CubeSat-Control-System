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

/*================================= CONSTANTS =================================*/
// Control Signal
#define DC_MAX      0.5     // Maximum Dutycycle value
#define DC_MIN      0       // Minimum Dutycycle value


// struct PidStruct{
//     float Kp{1};
//     float Ki{0};
//     float Kp{0};
    
//     float Tf{0};
// };

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
    float control();
    float control(float angle, float setpoint);
    void OpenLoopStep(float Dc_pwm);                // Apply Step directly into the plant (Open Loop)
    void ClosedLoopStep(float angle);               // Apply Step on the closed Loop (set reference)


    // Constructors:
    ControlSystem(float _kp, float _ki, float _kd, float _tf, float _ts);

};




float control(float Angle, float Setpoint){
    float Angle1[3]  = {0,0,0};      // Vector for Angle values 0 = current 
    float DC_out1[3] = {0,0,0};      // Vector for Dc values
    float Error1[3]  = {0,0,0};      // Vector for Error
    float Setpoint{0};              //
    float Angle, DC_out, Error;
    
    /* Error Signal */
    Error1[0]= Setpoint - Angle;

    /* CONTROL */
    DC_out=1;

    /* VARIABLE UPDATES */
    Angle1[2]= Angle1[1];
    Angle1[1]= Angle1[0];

    Angle1[2]= Angle1[1];
    Angle1[1]= Angle1[0];

    Angle1[2]= Angle1[1];
    Angle1[1]= Angle1[0];
    /* ANTI-WINDUP and SATURATION */
    //Anti- Windup

    // Saturation
    if(DC_out>DC_MAX){
        DC_out = DC_MAX;
    }
    if(DC_out<DC_MIN){
        DC_out = DC_MIN;
    }

    return DC_out;
}




#endif
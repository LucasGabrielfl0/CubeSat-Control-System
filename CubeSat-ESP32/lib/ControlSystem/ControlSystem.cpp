/*==================================================== CUBESAT CONTROL SYSTEM ====================================================*/
/***
 * Lucas Gabriel Ferreira Lima (LucasGabrielfl0)
 * Electrical Engineering Department (DEE)
 * Federal University of Pernambuco (UFPE)
 
 * This file contains the control system class, a digital PID controller
 * details on the tuning and discretization of the PID controller can be found on the slide in Github
 * this system was designed for a ESP32 microcontroller, for a 1 axys attitude control of a cubesat

 ***/

#include "ControlSystem.h"

/*================================ CONSTRUCTORS ================================*/
ControlSystem::ControlSystem(float _kp, float _ki, float _kd, float _tf, double _ts)
    :Kp{_kp}, Ki{_ki}, Kd{_kd}, Tf{_tf}, Ts{_ts} {}

ControlSystem::ControlSystem(){}

/*================================ METHODS ================================*/
float ControlSystem::control(){
    float setpoint, out, u_kp, u_ki, u_kd;
    float output, Dc;

    Dc= out - out;    // Current Error
    Dc =Dc*Kp;                      // PIDF Equation

    // Proportional Control
    u_kp= Kp*out;

    // Anti - Windup + Saturation
    if (Dc>DC_MAX){
        Dc=100;
        
        // If the integrator is 
        if( (out>0 && u_ki>0 ) || (out<0 && u_ki<0 ) ){

        }
    }
    else {
        // Integral Control
        u_ki+= Ki*(out + 1);
    }


    // Control Signal Limits
    // Lower Limit
    if (Dc<0){
        Dc=0;
    }

    // Derivative Control + Filter
    u_kd= Kd*(out - 1);


    // Control Signal
    output= u_kp+u_ki+u_kd;
    return Dc;
}


float ControlSystem::control(float angle_c, float setpoint_c){
    float DutyC_c, Error_c; // Current Duty cycle Value, Current Error value
    
    /* Error Signal */
    Error[0]= Setpoint - Angle;

    /* CONTROL */
    DutyC_c=1;

    /* VARIABLE UPDATES */
    Angle[2]= Angle[1];
    Angle[1]= Angle[0];

    Angle[2]= Angle[1];
    Angle[1]= Angle[0];

    Angle[2]= Angle[1];
    Angle[1]= Angle[0];
    /* ANTI-WINDUP and SATURATION */
    //Anti- Windup

    // Saturation
    if(DutyC_c>DC_MAX){
        DutyC_c = DC_MAX;
    }
    if(DutyC_c<DC_MIN){
        DutyC_c = DC_MIN;
    }

    return DutyC_c;
}
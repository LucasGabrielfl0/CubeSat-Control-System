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


/*================================= METHODS  =================================*/

void insideTask(){
    //while 1
    // get angle?
    // setPWM(GetDc());

}
void insideTask2(){
    //while 1
    // send shit via bluetooth
    // send shit

}

/*================================ CONSTRUCTORS ================================*/
ControlSystem::ControlSystem(float _kp, float _ki, float _kd, float _tf, float _ts)
    :Kp{_kp}, Ki{_ki}, Kd{_kd}, Tf{_tf}, Ts{_ts} {}


/*================================ METHODS ================================*/
float ControlSystem::control(){
    float setpoint, out, u_kp, u_ki, u_kd;
    float output, Dc;

    error_c= out - setpoint;    // Current Error
    Dc =error_c*Kp;                      // PIDF Equation

    // Proportional Control
    u_kp= Kp*error_c;

    // Anti - Windup + Saturation
    if (Dc>DC_MAX){
        Dc=100;
        
        // If the integrator is 
        if( (error_c>0 && u_ki>0 ) || (error_c<0 && u_ki<0 ) ){

        }
    }
    else {
        // Integral Control
        u_ki+= Ki*(error_c + error_prev);
    }


    // Control Signal Limits
    // Lower Limit
    if (Dc<0){
        Dc=0;
    }

    // Derivative Control + Filter
    u_kd= Kd*(error_c - error_prev);


    // Control Signal
    output= u_kp+u_ki+u_kd;


    // Updates error
    error_prev= error_c;

    return Dc;
}

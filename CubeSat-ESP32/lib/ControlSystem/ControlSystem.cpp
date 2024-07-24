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

float ControlSystem::control(float angle_c, int setpoint_c){
    float DutyC_c{0};

    /* Error Signal */
    Error[0]= setpoint_c - angle_c;

    /* CONTROL */
    DutyC[0]=Kp*(Error[0]-Error[2]) + Ki*(Ts/2)*(Error[0] + 2*Error[1] + Error[2]) + Kd*(2/Ts)*(Error[0]-2*Error[1] + Error[2]);
    

    /* VARIABLE UPDATES */
    Error[2]= Error[1];
    Error[1]= Error[0];

    DutyC[2]= DutyC[1];
    DutyC[1]= DutyC[0];

    DutyC_c = DutyC[0];
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
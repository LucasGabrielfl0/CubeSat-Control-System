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

ControlSystem::ControlSystem(){
    // CalcDiff();
}

/*================================ METHODS ================================*/
/* CALC DISCRETE DIFFERENTIAL EQUATION */
void ControlSystem::CalcDiff(){
    // NUM= N0 + N1*z^-1 + N2*z^-2
    N0=1;
    N1=3;
    N2=1;

    // DEN = 1 + D1*z^-1 + D2*z^-2
    D1=2;
    D2=3;
}

/* DISCRETE CONTROLLER [USING BILINEAR TRANSFORM] */
float ControlSystem::control(float angle_c, int setpoint_c){
    float DutyC_c{0};

    /* Error Signal */
    ek[0]= setpoint_c - angle_c;
    
    if(abs(ek[0])<MAX_ERROR){       // Error acceptance
        ek[0]=0;
    }

    /* CONTROL EQUATION */
    // uk[0]= Kp*ek[0] + Kd*(ek[0]-ek[1])/Ts;
    // uk[0]= (5.683*ek[0] - 5.689*ek[1] + uk[1])/0.995;
    
    uk[0]= 0.855*uk[1]+ 7.5*ek[0]  - 6.9*ek[1];
    
    // uk[0]= N0*ek[0] + N1*ek[1] + N2*ek[2] - D1*uk[1]- D2*uk[2];    

    /* VARIABLE UPDATES */
    ek[2]= ek[1];
    ek[1]= ek[0];

    uk[2]= uk[1];
    uk[1]= uk[0];

    DutyC_c = uk[0];
    
    /* SATURATION */
    if(DutyC_c>DC_MAX){
        DutyC_c = DC_MAX;
    }
    if(DutyC_c<DC_MIN){
        DutyC_c = DC_MIN;
    }

 
    /* System Shutdown*/
    if(shutdown == true){
        DutyC_c=0;
    }

    return DutyC_c;
}
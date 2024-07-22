/*==================================================== CUBESAT CONTROL SYSTEM ====================================================*/
/***
 * Lucas Gabriel Ferreira Lima (LucasGabrielfl0)
 * Federal University of Pernambuco (UFPE)
 
 * Main file for the Cubesat Attitude control system
 ***/

#include <Arduino.h>
#include <ControlSystem.h>
/*===================================== CONTROL PARAMETERS =====================================*/
//Gains
#define KP	1     	// Proporcional Gain
#define KI  1     	// Integral Gain
#define KD  1     	// Derivative Gain
#define TF  1		// Time constant of the Filter in the derivative gain 

#define TS  1e-3	// Sampling time in sec

/*==================================== OBJECTS =====================================*/

// Communication

// Control systems
ControlSystem PIDController(KP,KI,KD,TF,TS);

/*================================= GLOBAL VARIABLES =================================*/


// Sends data to the telemetry system every 1 ms
// Telemetry(float angle,float setpoint, float Dc);
// vtask
// Control System every 1 ms

/*===================================== SETUP =====================================*/
void setup() {

}

/*===================================== MAIN LOOP =====================================*/
void loop() {

}



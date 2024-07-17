/*==================================================== CUBESAT CONTROL SYSTEM ====================================================*/
/***
 * Lucas Gabriel Ferreira Lima (LucasGabrielfl0)
 * Federal University of Pernambuco (UFPE)
 
 * Main file for the Cubesat Attitude control system
 ***/

#include <Arduino.h>
#include <ControlSystems.h>

/*===================================== CONTROL PARAMETERS =====================================*/
//Gains
#define KP	1     	// Proporcional Gain
#define KI  1     	// Integral Gain
#define KD  1     	// Derivative Gain
#define TF  1		// Time constant of the Filter in the derivative gain 

#define TS  1e-3	// Sampling time in sec

/*==================================== OBJECTS =====================================*/
int myFunction(int, int);

// Control systems
PID pid1(KP,KI,KD,TF,TS);

/*================================= GLOBAL VARIABLES =================================*/




/*===================================== SETUP =====================================*/
void setup() {
  int result = myFunction(2, 3);

}

/*===================================== MAIN LOOP =====================================*/
void loop() {

}




// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}
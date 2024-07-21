/*==================================================== CUBESAT CONTROL SYSTEM ====================================================*/
/***
 * Lucas Gabriel Ferreira Lima (git: LucasGabrielfl0)
 * Federal University of Pernambuco (UFPE)
 
 * Main file for the Cubesat Attitude control system
 ***/

#include <Arduino.h>
#include "Wire.h"
#include "BluetoothSerial.h"
#include <MPU6050_Dark.h>         // Personalised
// #include <ControlSystem.h>     //
// #include <MotorControl.h>      //
// #include <BlueSerial.h>        //

/*===================================== CONTROL PARAMETERS =====================================*/
//Gains
#define KP	1     	// Proporcional Gain
#define KI  1     	// Integral Gain
#define KD  1     	// Derivative Gain
#define TF  1		// Time constant of the Filter in the derivative gain 

#define TS  1e-3	// Sampling time in sec

/*==================================== AUX FUNCTIONS =====================================*/
// Bluetooth
void Setup();
void SendData(float angle, float setpoint, float dutyc);
void TerminalCom();     // Sets communication via Terminal
 
/*==================================== OBJECTS =====================================*/
// Angle Sensor
MPU6050 mpu(Wire);

// Communication
BluetoothSerial Blue;

// Control systems
// ControlSystem PIDController(KP,KI,KD,TF,TS);

// Motor/Hbridge control
// MotorControl motor(IN1_PIN, IN2_PIN, ENA_PIN);

/*================================= GLOBAL VARIABLES =================================*/
float Setpoint{0};      // Angle setpoint in Degrees [°]
float AngleZ{0};         // Currente Angle value of the cubesat in Degrees [°]
float DutyC{0};         // DutyCycle of the PWM sent to the motor


/*===================================== SETUP =====================================*/
void setup() {
    Setup_blue();           // Setup of the Bluetooth Communication with the PC
    mpu.setup();            // Angle Sensor (MPU6050) setup and calibration
    // motor.setup();          // Motor and HBridge related Pins Setup

}


/*===================================== MAIN LOOP =====================================*/
void loop() {
    // Telemetry:
    // SendData_blue(1.0, 2.0, 3.0);

    // Receive data
}


/*===================================== AUX FUNCTIONS =====================================*/
/* Bluetooth */
void Setup_blue(){

}
void SendData_blue(float angle, float setpoint, float Dutyc){

}

void getData_blue(){

}
 


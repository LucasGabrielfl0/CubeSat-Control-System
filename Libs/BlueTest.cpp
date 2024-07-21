/*==================================================== CUBESAT CONTROL SYSTEM ====================================================*/
/***
 * Lucas Gabriel Ferreira Lima (LucasGabrielfl0)
 * Federal University of Pernambuco (UFPE)
 
 * Main file for the Cubesat Attitude control system
 ***/

#include <Arduino.h>
#include "Wire.h"
// #include <BlueSerial.h>
#include "Blue"

/*==================================== OBJECTS =====================================*/
// Communication
BlueSerial Blue;

/*================================= GLOBAL VARIABLES =================================*/
float Setpoint{0};      // Angle setpoint in Degrees [°]
float Angle{0};         // Currente Angle value of the cubesat in Degrees [°]
float DutyC{0};         // DutyCycle of the PWM sent to the motor


/*================================= RTOS =================================*/

// [Control System]: Apply control every 1 ms
void task(){
    // every 1ms
    // Get data from the sensor
    // Angle_Current = mpu6050.getAngle();
    // Dutyc= PIDController.control(Setpoint, Angle_current);
    // Motor.SetPWM(Dutyc);
}

// [Telemetry]: Sends data every 1 ms
// Telemetry(float angle,float setpoint, float Dc);

/*===================================== SETUP =====================================*/
void setup() {
    Blue.Setup();       // Setup of the Bluetooth Communication with the PC
    // AA               // Motor and HBridge related Pins Setup
    // aa               // Angle Sensor (MPU6050) setup and calibration
    // aa               // LED Setup
}


/*===================================== MAIN LOOP =====================================*/
void loop() {
    // Telemetry:
    Blue.SendData(1.0, 2.0, 3.0);

    // Receive data
}




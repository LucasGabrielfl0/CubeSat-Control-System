/*==================================================== CUBESAT CONTROL SYSTEM ====================================================*/
/***
 * Lucas Gabriel Ferreira Lima (git: LucasGabrielfl0)
 * Federal University of Pernambuco (UFPE)
 
 * Main file for the Cubesat Attitude control system
 ***/
#include <Arduino.h>
#include "Wire.h"
#include "BluetoothSerial.h"
#include <MPU6050_Dark.h>           // Angle Sensor
#include <MotorControl.h>           // Dc Motor control
// #include <ControlSystem.h>       // Control System
// #include <BlueSerial.h>          // ??

/*===================================== CONTROL PARAMETERS =====================================*/
//Gains
#define KP	1     	// Proporcional Gain
#define KI  1     	// Integral Gain
#define KD  1     	// Derivative Gain
#define TF  1		// Time constant of the Filter in the derivative gain 

#define INTERNAL_LED    2 

#define TS  1e-3	// Sampling time in sec

/*==================================== AUX FUNCTIONS =====================================*/
// Bluetooth
void Setup();
void SendData(float angle, float setpoint, float dutyc);
void TerminalCom();     // Sets communication via Terminal
 
/*==================================== OBJECTS =====================================*/
// Angle Sensor
// MPU6050 mpu(Wire);

// Communication
BluetoothSerial Blue;

// Control systems
// ControlSystem PIDController(KP,KI,KD,TF,TS);

// Motor/Hbridge control
MotorControl motor;

/*================================= GLOBAL VARIABLES =================================*/
float Setpoint{0};      // Angle setpoint in Degrees [°]
float AngleZ{0};         // Currente Angle value of the cubesat in Degrees [°]
float DutyC{0};         // DutyCycle of the PWM sent to the motor
uint8_t Dc_8b{0};

/*===================================== SETUP =====================================*/
void setup() {
    // Setup_blue();           // Setup of the Bluetooth Communication with the PC
    Serial.begin(115200);
    
    // mpu.setup();            // Angle Sensor (MPU6050) setup and calibration
    motor.setup();             //
}

/*===================================== MAIN LOOP =====================================*/
void loop() {
    motor.setPWM(DutyC);
    Serial.print("\nDutyc: ");
    Serial.print(DutyC);


    DutyC+=0.25;
    if(DutyC>1){
        DutyC=0;
    }
    
    // Receive data
    delay(2e3);
}


/*===================================== AUX FUNCTIONS =====================================*/
/* Bluetooth */
void Setup_blue(){
  Serial.begin(115200);
  Blue.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(INTERNAL_LED, OUTPUT);
  digitalWrite(INTERNAL_LED, HIGH);

}
void SendData_blue(float angle, float setpoint, float Dutyc){

}

void getData_blue(){
  if (Serial.available()) {
    Blue.write(Serial.read());
  }
  if (Blue.available()) {
    Serial.write(Blue.read());
  }
  delay(20);
}
 


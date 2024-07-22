/*==================================================== CUBESAT CONTROL SYSTEM ====================================================*/
/***
 * Lucas Gabriel Ferreira Lima (git: LucasGabrielfl0)
 * Federal University of Pernambuco (UFPE)
 
 * Main file for the Cubesat Attitude control system
 ***/
#include <Arduino.h>
#include "Wire.h"
#include "BluetoothSerial.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <MPU6050_Dark.h>           // Angle Sensor [Modified from MPU6050_Light]
#include <MotorControl.h>           // Dc Motor control [Personal]
#include <ControlSystem.h>          // Control System [Personal]
// #include <BlueSerial.h>          // ??

#define INTERNAL_LED    2 


/*==================================== OBJECTS ====================================*/
MPU6050 mpu(Wire);                      // Angle Sensor
BluetoothSerial Blue;                   // Communication
ControlSystem PIDController;            // Control systems
MotorControl motor;                     // Motor/Hbridge control


/*==================================== GLOBAL VARIABLES ====================================*/
int Setpoint{0};                    // Angle setpoint in Degrees [°]1
float AngleZ{0};                    // Currente Angle value of the cubesat in Degrees [°]
float DutyC{0};                     // DutyCycle of the PWM sent to the motor
float Error{0};                     // Error value;
uint8_t Dc_8b{0};                   // DutyCycle value in 8bits [0 to 255]
uint8_t SetpointFlag{1};            //

// Telemetry
char InMessage;                     //                     

// Time counter
uint32_t StartTime = millis();      //
uint32_t TimeCounter{0};            //


/* AUX FUNCTIONS */
// Bluetooth
void Setup_blue();
void TelemetryData(uint32_t timestamp, float angle, float setpoint, float dutyc);
void TerminalCom();         // Sets communication via Terminal
void TerminalCom2();        // Sets communication via Terminal
void LED_setup();           // LED Setup
 

/*==================================== TASKS =====================================*/
// Control system
void taskControl(void * params){
    while (true){
        // AngleZ = mpu.readAngleZ();
        // DutyC = PidController.control(AngleZ, Setpoint);
        // motor.setPWM(DutyC);
        vTaskDelay(1e3/portTICK_PERIOD_MS);   //Executes every 1ms
    }
}

// Telemetry data sent to the PC
void taskTelemetry(void * params){
    while (true){
        TimeCounter = millis() - StartTime;
        // Setpoint goes: =>0 =>90 => 0 => -90 => 0 .... every 6s
        if(TimeCounter>=6e3 && Setpoint==0){
            Setpoint = 90*SetpointFlag;            
        }
        if(TimeCounter>=12e3) {
            StartTime = millis();
            Setpoint = 0;
            SetpointFlag *= -1;
        }
        TelemetryData(TimeCounter , AngleZ ,Setpoint , DutyC);      // Send data to be plotted on PC 
        Serial.println(TimeCounter);                                // Serial Print of time
        vTaskDelay(1e3/portTICK_PERIOD_MS);                         //Executes Every 1ms
    }
}

// Get and send data via terminal
void taskBlueTerminal(void * params){
    while (true){
        Serial.println("TIME: 20S");
        Serial.println(millis());
        vTaskDelay(10e3/portTICK_PERIOD_MS);   //Executes every 20ms
    }
}


/*===================================== SETUP =====================================*/
void setup() {
    /* Systems Setup */
    Serial.begin(115200);
    // Setup_blue();            // Setup of the Bluetooth Communication with the PC
    // blue.setup();            // Setup of the Bluetooth Communication with the PC
    // motor.setup();           // Motor and HBridge related Pins Setup
    // mpu.setup();             // Angle Sensor (MPU6050) setup and calibration
    // LED_setup();             // LED Setup
    
    /* RTOS TASKs */
    xTaskCreatePinnedToCore(&taskControl, "ControlSystem", 1024, NULL, 3, NULL, 1);     // Task in core 1
    xTaskCreate(&taskTelemetry, "TelemetrySystem", 1024, NULL, 2, NULL);                // By default, in core 0
    xTaskCreate(&taskBlueTerminal, "Terminal", 1024, NULL, 1, NULL);                    // By default, in core 0
}

/*===================================== MAIN LOOP =====================================*/
void loop() {
    // jack shit
}





/*===================================== AUX FUNCTIONS =====================================*/
void LED_setup(){
}      



/* Bluetooth */
void Setup_blue(){
    Serial.begin(115200);
    Blue.begin("CUBESAT-ESP32");        //Bluetooth device name
    Serial.println("The device started, now you can pair it with bluetooth!");
    pinMode(INTERNAL_LED, OUTPUT);
    digitalWrite(INTERNAL_LED, HIGH);
}
void SendData_blue(float angle, float setpoint, float Dutyc){

}


void TerminalCom2(){
    if (Serial.available()) {
        Blue.write(Serial.read());
    }
    if (Blue.available()) {
        Serial.write(Blue.read());
    }
}

void TerminalCom(){
  if (Serial.available()) {
    Blue.write(Serial.read());
  }
  if (Blue.available()) {
    InMessage=(char)Blue.read();
    Serial.write(InMessage);
    switch (InMessage)
    {
    case '0':
        DutyC =0;
        break;
    case '2':
        DutyC =0.2;
        break;
    case '4':
        DutyC =0.4;
        break;
    case '5':
        DutyC =0.5;
        break;
    case '8':
        DutyC =0.8;
        break;
    
    default:
        break;
    }

  }
}
 


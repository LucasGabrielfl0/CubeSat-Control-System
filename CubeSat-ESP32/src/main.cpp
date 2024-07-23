/*==================================================== CUBESAT CONTROL SYSTEM ====================================================*/
/***
 * Lucas Gabriel Ferreira Lima (git: LucasGabrielfl0)
 * Federal University of Pernambuco (UFPE)
 
 * Main file for the Cubesat Attitude Control System
 ***/
#include <Arduino.h>
#include "Wire.h"
#include "BluetoothSerial.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <MPU6050_Dark.h>           // Angle Sensor [Modified from MPU6050_Light]
#include <BlueSerial.h>             // Bluetooth Communication [Modified from BluetoothSerial]
#include <MotorControl.h>           // Dc Motor control [Personal]
#include <ControlSystem.h>          // Control System [Personal]

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

/* LED Pins*/
// #define INTERNAL_LED    2       // [ALREADY USED BY BLUETOOTH CLASS]
// #define LED_BT          19      // [ALREADY USED BY BLUETOOTH CLASS]
#define LED_STOP        33      //
#define LED_LEFT        18      //
#define LED_RIGHT       32      //


/*==================================== GLOBAL VARIABLES ====================================*/
int Setpoint{0};                    // Angle setpoint in Degrees [°]
float AngleZ{0};                    // Currente Angle value of the cubesat in Degrees [°]
float DutyC{0};                     // DutyCycle of the PWM sent to the motor
float Error{0};                     // Error value;
int SetpointFlag{1};                // Aux flag used with the setpoint

// Time counter
uint64_t StartTime = millis();      // Time of reference in ms
uint32_t TimeCounter{0};            // Current time value in ms


/*==================================== OBJECTS ====================================*/
MPU6050 mpu(Wire);                  // Angle Sensor
BlueSerial Blue;                    // Communication
ControlSystem PIDController;        // Control systems
MotorControl motor;                 // Motor/Hbridge control (PWM setup, etc)


/* AUX FUNCTIONS */
void LED_setup();                           // LED Setup
 
/* TASKS PROTOTYPES */
void taskControl(void * params);            // Control System [Executes every 1ms]
void taskTelemetry(void * params);          // Sends data via Bluetooth [Executes every 1ms]
void taskBlueTerminal(void * params);       // Get and send data via terminal for manual mode [Every 20 ms]

/* SEMAPHORES */
xSemaphoreHandle ControlSemaphore;          // Only activates telemetry after control system


/*========================================= SYSTEM'S SETUP ========================================*/
void setup() {
    /* Systems Setup */
    Serial.begin(115200);
    Blue.setup();               // Setup of the Bluetooth Communication with the PC
    motor.setup();              // Motor and HBridge related Pins Setup
    // mpu.setup();                // Angle Sensor (MPU6050) setup and calibration
    // LED_setup();                // LED Setup
    
    /* Sempahore */
    ControlSemaphore = xSemaphoreCreateBinary();    // Creates binary sempahore

    /* RTOS TASKS */
    xTaskCreatePinnedToCore(&taskControl, "ControlSystem", 2048, NULL, 3, NULL, 1);             // Task in core 1
    xTaskCreatePinnedToCore(&taskTelemetry, "TelemetrySystem", 2048, NULL, 2, NULL,0);          // By default, in core 0
    xTaskCreatePinnedToCore(&taskBlueTerminal, "Terminal", 1024, NULL, 0, NULL,0);              // By default, in core 0
}

/*===================================== MAIN LOOP =====================================*/
void loop() {
    // jack shit
}


/*===================================== TASKS =====================================*/
void taskControl(void * params){
    while (true){
        // AngleZ = mpu.readAngleZ();                                      // Reads sensor data
        // DutyC = PidController.control(AngleZ, float(Setpoint));         // Gets DutyCycle value calculated by the control
        motor.setPWM(DutyC);                                            // Sets PWM acordingly to Dc value
        // Serial.println("FLAG 1");        

        xSemaphoreGive(ControlSemaphore);                               // After control is done, allows others
        vTaskDelay(1/portTICK_PERIOD_MS);                               // Task delay of 1 ms
    }
}

// Telemetry data sent to the PC [Ts = 1ms]
void taskTelemetry(void * params){
    while (true){
        TimeCounter = millis() - StartTime;                         // TimeStamp
        xSemaphoreTake(ControlSemaphore, portMAX_DELAY);            // Holds task indefinetly until Control task is over

        /* Setpoint Shift*/ // Setpoint goes: =>0 =>90 => 0 => -90 => 0 .... every 6s
         if(TimeCounter>=6e3 && Setpoint==0){
            Setpoint = 90*SetpointFlag;            
        }
        if(TimeCounter>=12e3) {
            StartTime = millis();
            Setpoint = 0;
            SetpointFlag *= -1;
        }
        // Serial.println("FLAG 2");        
        Blue.TelemetryPrint(TimeCounter , AngleZ ,Setpoint , DutyC);        // Send data to be plotted on PC 
        vTaskDelay(1/portTICK_PERIOD_MS);                                   // Executes Every 1ms
    }
}

// Get and send data via terminal [Every 20 ms] [MANUAL MODE: FOR TESTS ONLY]
void taskBlueTerminal(void * params){
    while (true){
        Blue.GetFromTerminal(Setpoint, DutyC);                      // Update values from Terminal             
        vTaskDelay(20/portTICK_PERIOD_MS);                          //Executes every 20ms
    }
}




/*===================================== AUX FUNCTIONS =====================================*/
void LED_setup(){
    pinMode(LED_LEFT, OUTPUT);
    pinMode(LED_RIGHT, OUTPUT);
    pinMode(LED_STOP, OUTPUT);
}      


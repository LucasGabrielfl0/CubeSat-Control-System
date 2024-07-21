/*==================================================== CUBESAT CONTROL SYSTEM ====================================================*/
/***
 * Lucas Gabriel Ferreira Lima (LucasGabrielfl0)
 * Electrical Engineering Department (DEE)
 * Federal University of Pernambuco (UFPE)
 
 *

 ***/
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

void Telemetry(float angle,float setpoint, float Dc){
    float time_c= millis();
    float Duty= Dc*100;
    printf("[Cubesat]: Time: %2.f ms | Angle: %.2f ° | Setpoint: %.2f° | Dutycycle: %.2f%", time_c, angle, setpoint, Duty);

}

void getUserData(){
    
}
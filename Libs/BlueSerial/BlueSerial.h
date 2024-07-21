/*==================================================== CUBESAT CONTROL SYSTEM ====================================================*/
/***
 * Lucas Gabriel Ferreira Lima (LucasGabrielfl0)
 * Electrical Engineering Department (DEE)
 * Federal University of Pernambuco (UFPE)
 
 *

 ***/

#ifndef _BLUE_SERIAL_H_
#define _BLUE_SERIAL_H_
#include "BluetoothSerial.h"

void Setup();
void SendData(float angle, float setpoint, float Dutyc);
void getData();
 
class BlueSerial: public BluetoothSerial{
    // Methods
    public:
    void Setup();
    void SendData(float angle, float setpoint, float Dutyc);
    void getData();
    
    // Constructor
    BlueSerial(void);
};
BlueSerial::BlueSerial(){}

void BlueSerial::Setup(){
    begin("ESP32 - LGFL");      //Bluetooth device name
}

void BlueSerial::SendData(float angle,float setpoint, float Dutyc){
    // char buffer[50];
    // sprintf(buffer, "[CAN]: Angle: %.2f° | %.2f° | %.2f%", angle, setpoint, Dutyc);
    // println(buffer);    
    
    char buff[50];
    // float time_c= millis();
    float Duty= Dutyc*100;
    sprintf(buff,"[Cubesat]: Angle: %.2f° | Setpoint: %.2f° | Dutycycle: %.2f%", angle, setpoint, Duty);
    println(buff);    

    // // println(String("[CAN]: Angle:") + angle + "° | Setpoint:" + setpoint + "° | Dutycycle:" + Dutyc+ "%");
}


#endif

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

#define INTERNAL_LED    2

void Setup();
void SendData(float angle, float setpoint, float Dutyc);
void getData();
 
class BlueSerial: public BluetoothSerial{
    // Methods
    public:
    void Setup();
    void GetFromTerminal(float &Setpoint, float &DutyCycle);
    void TerminalChat();
    void TelemetryPrint(uint32_t timestamp, float angle, int setpoint, float dutyc);
    void getData();
    
    // Constructor
    BlueSerial(void);
};
BlueSerial::BlueSerial(){}



#endif

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
#define CUBESAT_LED     19
class BlueSerial: public BluetoothSerial{
    // Methods
    public:
    void setup();
    void GetFromTerminal(int &Setpoint, float &DutyCycle);
    void TerminalChat();
    void TelemetryPrint(uint32_t timestamp, float angle, int setpoint, float dutyc);
    
    // Constructor
    BlueSerial(void);
};


#endif

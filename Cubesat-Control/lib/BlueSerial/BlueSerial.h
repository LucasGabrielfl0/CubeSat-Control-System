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


class BlueSerial: public BluetoothSerial
{

    // Methods
    public:
    void BlueSetup();
    void SendData(float Angle, float Ref, float Dc);
    void getData();
    
    // Constructor
};

#endif

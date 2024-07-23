/*==================================================== CUBESAT CONTROL SYSTEM ====================================================*/
/***
 * Lucas Gabriel Ferreira Lima (LucasGabrielfl0)
 * Electrical Engineering Department (DEE)
 * Federal University of Pernambuco (UFPE)
 
 * Bluetooth 

 ***/
#include "BlueSerial.h"

// #if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
// #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
// #endif

void BlueSerial::Setup(){
    Serial.begin(115200);
    begin("CUBESAT-ESP32");                         //Bluetooth device name
    Serial.println("[Bluetooth]: Blue is active");
    pinMode(INTERNAL_LED, OUTPUT);
    digitalWrite(INTERNAL_LED, HIGH);

}

void BlueSerial::TelemetryPrint(uint32_t timestamp, float angle, int setpoint, float dutyc){
    // send
    printf("[CUBESAT]: Time: %d | Angle %.2f° | Setpoint: %d | Dc= %.2f\n", timestamp, angle, setpoint, dutyc);
}


void BlueSerial::TerminalChat(){
    if (Serial.available()) {
        write(Serial.read());
    }
    if (available()) {
        Serial.write(read());
    }
}



void BlueSerial::GetFromTerminal(float &Setpoint, float &DutyC){
    char InMessage;
//   if (Serial.available()) {
//     Blue.write(Serial.read());
//   }
  if (available()) {
    InMessage=(char)read();
    // Serial.write(InMessage);
    switch (InMessage) {
        /* DutyCycle*/
        case '0':
            DutyC =0;
            break;
        case '1':
            DutyC =0.1;
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

        /* Setpoint */
        case 'F':
            Setpoint =90;
            break;
        case 'A':
            Setpoint =-90;
            break;
        case 'N':
            Setpoint =0;
            break;

        default:
        break;
    }

  }
}

void BlueSerial::TerminalChat(){
    if (Serial.available()) {
        write(Serial.read());
    }
    if (available()) {
        Serial.write(read());
    }
}

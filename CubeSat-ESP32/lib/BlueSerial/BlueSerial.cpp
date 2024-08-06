/*==================================================== CUBESAT CONTROL SYSTEM ====================================================*/
/***
 * Lucas Gabriel Ferreira Lima (LucasGabrielfl0)
 * Electrical Engineering Department (DEE)
 * Federal University of Pernambuco (UFPE)
 
 * Bluetooth 

 ***/
#include "BlueSerial.h"

/*================================ CONSTRUCTORS ================================*/
BlueSerial::BlueSerial(){}


/*================================ METHODS ================================*/
/* SETUP FUNCTION */
void BlueSerial::setup(){
    begin("CUBESAT-ESP32");                             //Bluetooth device name
    Serial.println("[Bluetooth]: Blue is active");      // Initial message

    pinMode(INTERNAL_LED, OUTPUT);                      // INTERNAL LED
    digitalWrite(INTERNAL_LED, HIGH);

    pinMode(CUBESAT_LED, OUTPUT);                      // Cubesat LED
    digitalWrite(CUBESAT_LED, HIGH);

}


/* PRINT DATA IN BLUETOOTH TERMINAL*/
void BlueSerial::TelemetryPrint(uint32_t timestamp, float angle, int setpoint, float dutyc){
    // send
    printf("[CUBESAT]: Time: %d | Angle %.2f° | Setpoint: %d | Dc= %.2f\n", timestamp, angle, setpoint, dutyc);
}


/* UPDATES VARIABLES FROM BLUETOOTH TERMINAL*/
void BlueSerial::GetFromTerminal(int &Setpoint, float &DutyC){
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
        case '3':
            DutyC =0.3;
            break;
        case '4':
            DutyC =0.4;
            break;
        case '5':
            DutyC =0.5;
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
        case 'S':
            Setpoint =-300;
            break;
        case 'G':
            Setpoint =-400;
            break;

        default:
        break;
    }

  }
}


/* OPENS CHAT TO SEND AND GET DATA*/
void BlueSerial::TerminalChat(){
    if (Serial.available()) {
        write(Serial.read());
    }
    if (available()) {
        Serial.write(read());
    }
}


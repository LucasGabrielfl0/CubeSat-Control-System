import numpy as np
import re
import serial
import time
#=========================================== COMMUNICATION SETUP ===========================================#
PC_PORT         =   'COM12'
BAUD_RATE       =   115200
ser= serial.Serial(PC_PORT, BAUD_RATE)

#=========================================== AUX FUNCTIONS ===========================================#
# Confirms ID
def ID_confirm(Data_string):
    Id= Data_string.split(":")
    if Id[0] == '[CUBESAT]':
        return True
    else:
        return False


# Create/Resets data arrays
def NewArrays():
    y1          = np.zeros(0,float)
    time_data   = np.zeros(0,float)
    start_time  = 0
    
    return time_data, y1, y1, y1, start_time


#=========================================== SERIAL READER ===========================================#
# message example:'[Cubesat]: Angle: 10.00 ° | Setpoint: 20.00° | Dutycycle: 50.00%'
def ReadSerial(time_data, y1_control, y2_ref, y3_response,start_time):
    # Keeps reading until finds right msg
    while True:
        ESP32_Data= ser.readline().decode('utf8')           # Read Serial  
        Data_Array=re.findall(r"[\d.]+", ESP32_Data)
        if len(Data_Array) ==4:
                break

    print(Data_Array)
    # Get Current Values for each variable
    time_c      = float(Data_Array[0])
    response_c  = float(Data_Array[1])
    ref_c       = float(Data_Array[2])
    control_c   = float(Data_Array[3])

    #time
    time_c = time_c- start_time

    # Add the current value to the Data array
    time_data       = np.append(time_data       , time_c)
    y1_control      = np.append(y1_control      , control_c)
    y2_ref          = np.append(y2_ref          , ref_c)
    y3_response     = np.append(y3_response     , response_c)

    if time_data.size == 1:
        start_time = time_c
        time_data = time_data - start_time


    # Returns all arrays
    return time_data, y1_control, y2_ref, y3_response,start_time

# time_data, y1_control, y2_ref, y3_response,time_c =NewArrays()
# while True:
#     time_data, y1_control, y2_ref, y3_response,time_c = ReadSerial(time_data, y1_control, y2_ref, y3_response,time_c)
# #     ESP32_Data= ser.readline().decode('utf8') 
#     Data_Array=re.findall(r"[\d.]+", ESP32_Data)
#     print(Data_Array)
#     time.sleep(0.001)
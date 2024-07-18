import numpy as np
import re
import serial
import time
#=========================================== COMMUNICATION SETUP ===========================================#
PC_PORT = 'COM10'
BAUD_RATE = 9600

ser= serial.Serial(PC_PORT, BAUD_RATE)

# Create/Resets data arrays
def NewArrays():
    y1          = np.zeros(0,float)
    time_data   = np.zeros(0,float)
    start_time  = 0
    
    return time_data, y1, y1, y1, start_time

# Read Data from serial port and stores it's values in the array
# message example:'[Cubesat]: Time: 1000.00 ms | Angle: 10.00 ° | Setpoint: 20.00° | Dutycycle: 50.00%'
def ReadSerial(start_time, time_data, y1_control, y2_ref, y3_response):
    # Keeps reading until finds right msg
    while True:
        ESP32_Data= ser.readline().decode('ascii')           # Read Serial  
        Data_Array=re.findall(r"[\d.]+", ESP32_Data)        # Get only the numbers from serial data
        
        if Data_Array:      # Only goes out of the loop if reads something
            break        
    print(Data_Array)
    
    # Get Current Values for each variable
    time_c      = float(Data_Array[0])
    response_c  = float(Data_Array[1])
    ref_c       = float(Data_Array[2])
    control_c   = float(Data_Array[3])

    time_c   = time_c - start_time

    # Add the current value to the Data array
    time_data       = np.append(time_data       , time_c)
    y1_control      = np.append(y1_control      , control_c)
    y2_ref          = np.append(y2_ref          , ref_c)
    y3_response     = np.append(y3_response     , response_c)

    # Returns all arrays
    return start_time, time_data, y1_control, y2_ref, y3_response


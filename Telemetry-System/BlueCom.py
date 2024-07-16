#=================================================== Bluetooth Communication ===================================================#
 # Lucas Gabriel Ferreira Lima
 # Federal University of Pernambuco (UFPE)
 # Control Engineering Laboratory
 
 # This file contains the code for the communication between a esp32 and a PC via Bluetooth
 # 
import numpy as np

























# Creates Empty Arrays to Store variables
def NewArrays():
    time_cons= 0
    time_array=np.zeros(0,float)
    y1=np.zeros(0,float)
    y2=np.zeros(0,float)
    y3=np.zeros(0,float)
    y4=np.zeros(0,float)

    return time_array, y1, y2, y3, y4, time_cons

def ReadBlue(time_array, y1_control, y2_ref, y3_response, y_, start_time):
    Data_Array=[]
    getBlue()

    # Get Current Values for each variable
    time_c      = float(Data_Array[0])
    control_c   = float(Data_Array[1])
    ref_c       = int(Data_Array[5])
    response_c  = int(Data_Array[6])

    # Removes time offset
    time_c= time_c - start_time
    
    # Add the current value to the Data array
    time_data   = np.append(time_data   , time_c)
    y1_dc       = np.append(y1_dc       , control_c)
    y2_rpm      = np.append(y2_rpm      , ref_c)
    y30_Tm      = np.append(y30_Tm      , response_c)

    return time_array, y1_control, y2_ref, y3_response, y_, start_time


# message example:'[ESP32]: | TIME: 500.12 sec | DC= 80.11 % |  REF= 45.5° | RESPONSE = 80.25° |
def getBlue():
    pass

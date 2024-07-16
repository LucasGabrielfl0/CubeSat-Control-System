import numpy as np

def NewArraysTest():
    start_time= 0
    y_=np.zeros(0,float)
            # 1. Time array, 2. control, 3. ref, 4. response 
    return  y_, y_, y_, y_, start_time


def ReadTest(time_array, y1_control, y2_ref, y3_response, time_count):
    value=50*np.sin((100 / (10*2** 10)) * 2 * np.pi * time_count) + 50
    
    # Add the current value to the Data array
    y1_control      = np.append(y1_control       , value)
    y2_ref          = np.append(y2_ref      , 0)
    y3_response     = np.append(y3_response      , value-50)

    time_array=np.append(time_array, time_count)
    time_count= time_count+1

    return time_array, y1_control, y2_ref, y3_response, time_count

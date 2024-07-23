import numpy as np
# Create/Resets data arrays
y1          = np.zeros(0,float)
time_data   = np.zeros(0,float)
start_time  = 0
    
time_data=np.append(time_data,1)
time_data=np.append(time_data,2)
time_data=np.append(time_data,3)

print(time_data)
if time_data[0] != 0:
    time_data=time_data - time_data[0]
print(time_data)

# if y1.size>0:
#     print("hm")

# if time_data:
#     print(time_data[-1])
#     print("right")
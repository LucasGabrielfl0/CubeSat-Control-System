#=================================================== ESP32 BLUETOOTH MONITOR ===================================================#
 # Lucas Gabriel Ferreira Lima (LucasGabrielfl0)
 # Federal University of Pernambuco (UFPE)
 # Control Engineering Laboratory
 
 # This file contains the code for the ESP32 live monitoring system via Bluetooth
 # 
 
#=================================================== LIBRARIES ===================================================#
from matplotlib import pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np
import time

# Library to change theme
import matplotx
plt.style.use(matplotx.styles.dracula)

# Custom Libs
from CSVDatalogger import *     # Logs data in .CSV   
from PlotSettings import *      # Figure Settings
from SineTest import *          # Test Mode (plot without Bluetooth)
from BlueCom import *           # Bluetooth Communicaiton with ESP32

TEST_MODE = True
if TEST_MODE:
    NewArrays = NewArraysTest
    ReadBlue = ReadTest

#------------------------------------------------- PLOT UPDATE: BLITING + AUTO AXYS ----------------------------------------------#
# Animated Plot
def update_plot(frame, frame_times):
    global time_data, start_time
    global y1_Control, y2_Ref, y3_Response

    # Update Values
    time_data, y1_Control, y2_Ref, y3_Response, start_time = ReadBlue(time_data, y1_Control, y2_Ref, y3_Response, start_time)
    
    # If the Time array doesnt start from zero, sets the start time
    if time_data[0]>0:
        start_time= time_data[0]
        time_data = time_data - start_time


    frame_times[frame] = time.perf_counter()
    print("Time: ",time_data[frame],"  volt: ",y3_Response[frame])

    # Updates the lines of the Graph
    line1_Control.set_data(time_data     , y1_Control)
    line2_Ref.set_data(time_data         , y2_Ref)
    line3_Response.set_data(time_data    , y3_Response)
    
    # Only rescales if necessary
    rescale = False

    # Update Time Axys
    if time_data[frame] > ax1_control.get_xlim()[1]:
        ax2_Response.set_xlim(ax1_control.get_xlim()[0], ax1_control.get_xlim()[1] + MAX_FRAMES / 5)
        ax1_control.set_xlim(ax1_control.get_xlim()[0], ax1_control.get_xlim()[1] + MAX_FRAMES / 5)
        rescale = True

    if frame == len(time_data) - 1:
        rescale = True
    
    if rescale:
        fig.canvas.draw()
    
    # If it gets to the last frame, clears graphs and Logs data 
    if frame==MAX_FRAMES-1:
        LogData(time_data, y1_Control, y2_Ref, y3_Response)
        time_data, y1_Control, y2_Ref, y3_Response, start_time = NewArrays()


    return line1_Control ,line2_Ref, line3_Response,


#================================================ MAIN ================================================#
time_data, y1_Control, y2_Ref, y3_Response, start_time = NewArrays()
fig, ax1_control, ax2_Response, titl, line1_Control ,line2_Ref, line3_Response = create_figure()

fig.suptitle(t="CUBESAT: Attitude Monitor", fontsize=10,backgroundcolor='red',fontweight='bold')
frame_times = np.zeros(MAX_FRAMES)


# Creates Loop and Plots the Animation:
ani = FuncAnimation(fig, update_plot, interval=0, fargs=(frame_times,), repeat=True, frames=list(range(MAX_FRAMES)), blit=True)
plt.show()

LogData(time_data, y1_Control, y2_Ref, y3_Response)

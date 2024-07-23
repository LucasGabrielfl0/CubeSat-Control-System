#=================================================== PLOT SETTINGS ===================================================#
 # Lucas Gabriel Ferreira Lima
 # Federal University of Pernambuco (UFPE)
 # Control Engineering Laboratory
 
 # This file contains the code for settings of the live monitoring system graph
from matplotlib import pyplot as plt
import numpy as np

#=================================================== GRAPH PARAMETERS ===================================================#
# Graph Limits
CONTROL_MAX     =   110     # Maximum value of the control signal
RESPONSE_MAX    =   120     # Maximum value of the systems Response
RESPONSE_MIN    =   -120    # Minimum value of the systems Response
XLIM_MAX        =   12000    # Maximum value of the time axys (in the initial plot)

# Ticks
TICK_CONTROL    =   25
TICK_RESPONSE   =   30
TICK_TIME       =   1000

MAX_FRAMES      =   860    # Maximum number of points in the graph before reseting
LINE_WEIGTH     =   2       # Line weight

#------------------------------------------------- LINE/FIGURE SETTINGS ----------------------------------------------#
# Create Figure, Axys and Lines
def create_figure():
    # Graph Parameters
    plt.rcParams["figure.figsize"] = (12, 4)
    fig = plt.figure(figsize=(12, 6), tight_layout=True)
    fig.canvas.manager.set_window_title('Attitude Control Monitor')

    # Define the layout using subplot2grid
    ax1_control     = plt.subplot2grid((3, 2), (0, 0), colspan=2)
    ax2_Response      = plt.subplot2grid((3, 2), (1, 0), colspan=2, rowspan=2)

    # Lines
    line1_Control, = ax1_control.plot([], [], lw=LINE_WEIGTH, color='#C7F9CC')
    line2_Ref, = ax2_Response.plot([], [], lw=LINE_WEIGTH)
    line3_Response, = ax2_Response.plot([], [], lw=LINE_WEIGTH)

    titl = ax1_control.set_title('Left Plot Title')
    
    # Graph 1: CONTROL
    ax1_control.set_ylim(0, CONTROL_MAX)
    ax1_control.set_xlim(0,XLIM_MAX)
    ax1_control.set_title('DutyCycle')
    ax1_control.set_ylabel('Percentage [%]')
    ax1_control.set_yticks(np.arange(0, CONTROL_MAX+1,TICK_CONTROL))
    # ax1_control.set_xticks(np.arange(0, XLIM_MAX+1,TICK_TIME))
    ax1_control.grid(True)

    # Graph 3: OUTPUT
    ax2_Response.set_ylim(RESPONSE_MIN, RESPONSE_MAX)
    ax2_Response.set_xlim(0,XLIM_MAX)
    ax2_Response.set_title('Angle')
    ax2_Response.set_ylabel('Degrees [°]')
    ax2_Response.set_xlabel('time [ms]')
    ax2_Response.set_yticks(np.arange(RESPONSE_MIN, RESPONSE_MAX+1,TICK_RESPONSE))
    # ax2_Response.set_xticks(np.arange(0, XLIM_MAX+1,TICK_TIME))
    ax2_Response.grid(True)
    ax2_Response.legend([line2_Ref, line3_Response], ['Reference', 'Response'], loc="upper left")    

    return (fig, ax1_control,ax2_Response, titl, line1_Control, line2_Ref, line3_Response)

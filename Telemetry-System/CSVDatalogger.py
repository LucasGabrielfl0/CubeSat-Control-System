#=================================================== CSV DATA LOGGER ===================================================#
 # Lucas Gabriel Ferreira Lima
 # Federal University of Pernambuco (UFPE)
 # Control Engineering Laboratory
 
 # This file contains the code for the data logger of the monitoring system
 # it just saves the np arrays in a .csv file
 
import csv

def LogData(time_data_, y1_control, y2_ref, y3_response):
    #Header (Name of each collumn)
    HEADER = ['Time', 'Control Signal', 'Reference','Response']
    
    #Save data in a .csv file
    with open('Telemetry-System/Data_Logging/EXPERIMENTAL_DATA.csv', 'w', encoding='UTF8', newline='') as f:
        writer = csv.writer(f)      #
        writer.writerow(HEADER)     #
        
        # Saves every array as a column
        for time_ms, Control, Reference, Response in zip(time_data_, y1_control, y2_ref, y3_response):
            writer.writerow([time_ms,Control, Reference, Response,])
    # Done!
    print('[Data Logger]: Data saved!, you have [',len(time_data_),'] Logs!')

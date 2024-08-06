%% Data Preprocessing
% Code used to preprocess .csv raw file into a processed .mat file
clc
clear

% Import Experimental data
Data=readmatrix("ControlData.csv");
time_sec  = Data(:,1);
Response_angle = Data(:,2);

step270_index= find(time_sec==54.532);

% Setpoint Array
Setpoint_angle = ones(size(time_sec));
Setpoint_angle(1:step270_index) = 90;
Setpoint_angle(step270_index:end) = 270;


% Time shift to keep everything in seconds
for i=49:1:113
    time_sec(i)=time_sec(i) + 60;
end


% Plot:
hold on
plot(time_sec,Response_angle)
plot(time_sec,Setpoint_angle)
legend('Response', 'Setpoint')
grid on

disp('Data Imported')
%% Trim Data
% Get the useful part:
start_index=1;
end_index =find(time_sec== 68.667);

% Trim data
time_sec        = time_sec(start_index:end_index);
Response_angle  = Response_angle(start_index:end_index);
Setpoint_angle  = Setpoint_angle(start_index:end_index);


% Plot:
hold on
plot(time_sec,Response_angle)
plot(time_sec,Setpoint_angle)
legend('Response', 'Setpoint')
grid on

disp('Stage 1: csv trash removed')
clear start_index end_index
%% Remove Offset + Trim
start_index =1;

% Trim data
% Step: 120
time_sec_180        = time_sec(step270_index:end);
Response_angle_180  = Response_angle(step270_index:end);
Setpoint_angle_180  = Setpoint_angle(step270_index:end);

time_sec_180        = time_sec_180 - time_sec_180(1);
Response_angle_180  = Response_angle_180 - Response_angle_180(1);
Setpoint_angle_180  = Setpoint_angle_180 - 90; 


% Plot:
close all
hold on
plot(time_sec_180,Response_angle_180)
plot(time_sec_180,Setpoint_angle_180)
legend('Response', 'Setpoint')

grid on

disp('Stage 2: offset removed')


%% Remove Offset + Trim
%step 45
step270_index =step270_index-1;
time_sec_47        = time_sec(1:step270_index);
Response_angle_47  = Response_angle(1:step270_index);
Setpoint_angle_47  = Setpoint_angle(1:step270_index);

time_sec_47        = time_sec_47 - time_sec_47(1);
Setpoint_angle_47  = Setpoint_angle_47 - 43; 
Response_angle_47  = Response_angle_47 - Response_angle_47(1);



% Plot:
close all
hold on
plot(time_sec_47,Response_angle_47)
plot(time_sec_47,Setpoint_angle_47)
legend('Response', 'Setpoint')

grid on

disp('Stage 3: extra step')


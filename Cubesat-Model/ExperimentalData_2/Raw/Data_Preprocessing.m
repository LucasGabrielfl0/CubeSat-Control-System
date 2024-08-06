%% Data Preprocessing
% Code used to preprocess .csv raw file into a processed .mat file
clc
clear

% Import Experimental data
Data=readmatrix("TestData_Dc40.csv");
time_sec  = Data(:,1);
Response_angle = Data(:,2);
% Dc = Data(:,4);

% Plot:
plot(time_sec,Response_angle)
grid on

disp('Data Imported')
%% Trim Data
% Get the useful part:
start_index=50;
end_index=450;

time_sec = time_sec(start_index:end_index);
Response_angle    = Response_angle(start_index:end_index);

% Plot:
plot(time_sec,Response_angle)
grid on

disp('Stage 1: csv trash removed')
clear start_index end_index
%% Remove Offset
time_sec = time_sec - time_sec(1);
Response_angle    = Response_angle - Response_angle(1);
 
% Plot:
close all
plot(time_sec,Response_angle)
grid on

disp('Stage 2: offset removed')


hold on
Gp_s   = tf(120,[1 0 0]);         % Tuned Model
step(0.4*Gp_s, time_sec(end))

grid on
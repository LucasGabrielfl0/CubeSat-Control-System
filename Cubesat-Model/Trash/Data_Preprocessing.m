%% Data Preprocessing
% Code used to preprocess .csv raw file into a processed .mat file
clc
clear

% Import Experimental data
Data=readmatrix("Experimental_data\Raw_data\data_1_D40.csv");
time_ms  = Data(:,1);
angle = Data(:,2);
Dc = Data(:,4);

disp('Data Imported')

%% Trim Data
% Get the useful part:
start_index=2651;
end_index=3162;

time_ms  = time_ms(start_index:end_index);
angle = -angle(start_index:end_index);
Dc=Dc(start_index:end_index);

disp('Stage 1: csv trash removed')

%% Remove Offset
time_ms  = time_ms - time_ms(1);
angle = angle - angle(1);
 

disp('Stage 2: offset removed')

% Plot
hold on
plot(time_ms, angle);
% plot(time_ms, Dc);
grid on








%% TRASH
% y= a*t
% % (K/s^3) => K(t^2)/2
% % a=K/2 => K=2*a
% close all
% y1=9e5;
% t1=601;
% a= y1/(t1*t1);
% k2=2*a;
% t=0:1:900;
% yt=a*t.*t;
% hold on
% plot(t,yt, 'g--')
% step(Cubesat2)
% grid on
% legend('Model', 'Plant')
% disp(k2)
% % grid on

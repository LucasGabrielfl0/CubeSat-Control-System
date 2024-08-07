%% Data Preprocessing
% Code used to preprocess .csv raw file into a processed .mat file
clc
clear

% Import Experimental data
Data=readmatrix("Experimental_data_Dc_50\data.csv");
time_ms  = Data(:,1);
time_sec = time_ms/1000;
angle = -Data(:,2);
Dc = Data(:,4);

disp('Data Imported')
hold on
plot(time_sec, Dc);
plot(time_sec, angle);
grid on
% hold on
%% Trim Data
% Get the useful part:
start_index=663;
end_index=4689;

time_sec  = time_sec(start_index:end_index);
angle = angle(start_index:end_index);
Dc=Dc(start_index:end_index);

plot(time_sec, angle);
grid on

disp('Stage 1: csv trash removed')
clear start_index end_index
%% Remove Offset
time_sec  = time_sec - time_sec(1);
angle = angle - angle(1);
 

disp('Stage 2: offset removed')

close all

plot(time_sec, angle);
grid on
%% Plot
close all
hold on
plot(time_sec, angle);


s=tf('s');
k_tuned=130;
Gp_s=k_tuned/(s*s);
step(0.5*Gp_s,2,'--m')

% legend('1','2')
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

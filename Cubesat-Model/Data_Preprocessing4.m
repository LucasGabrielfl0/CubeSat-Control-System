%% Data Preprocessing
% Code used to preprocess .csv raw file into a processed .mat file
clc
clear

% Import Experimental data
Data=readmatrix("Raw_data2\data3.csv");
Data2=readmatrix("Raw_data2\data_time2.csv");

angle2 = Data2(:,2);
time_sec2=Data2(:,1);

angle = Data(:,2);
n=numel(angle);
time_sec  = linspace(0,n,n);
time_sec = reshape(time_sec,670,1);
% time_sec=time_sec/1000;
% Dc = Data(:,4);

disp('Data Imported')
plot(time_sec, angle);
% plot(time_sec2, angle2);
grid on


% %% Trim Data
% % Get the useful part:
% start_index=2651;
% end_index=3162;
% 
% % time_sec2  = time_sec2(start_index:end_index);
% angle = -angle(start_index:end_index);
% Dc=Dc(start_index:end_index);
% 
% disp('Stage 1: csv trash removed')

%% Remove Offset
time_sec2  = time_sec2 - time_sec2(1);
angle2 = angle2 - angle2(1);

time_sec  = time_sec - time_sec(1);
angle = angle - angle(1);


close all

disp('Stage 2: offset removed')

% Plot
hold on
plot(time_sec2, angle2,'r');
plot(time_sec, angle, 'y');
% plot(time_ms, Dc);
grid on



%% compare
% close all

k=90;
model=tf(k,[1 0 0]);
step(0.4*model,time_sec2(end),'--b');



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

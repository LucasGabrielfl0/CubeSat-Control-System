%% Grey Box Model of the Cubesat
clc
clear
s=tf('s');

%% Experimental x Continuous Model
% Import Experimental data [Already processed]
load("Experimental_data\AngleZ_data.mat");
load("Experimental_data\DutyC_data.mat");
load("Experimental_data\time_ms.mat");
time_sec=time_ms/1000;
% time_ms=time_ms;
% Plot
hold on
subplot(2,1,1)
plot(time_sec, angle);       % Response
grid on
legend('DutyCycle (Input)')

subplot(2,1,2)
plot(time_sec, Dc);          % Input (Step from 0 to 0.4)
grid on
legend('Angle (Response)')

%% COMPARE MODEL
% Continuous Model
y1=angle(400);
t1=time_sec(400);

k_1 = y1*2/(t1*t1*0.4);     % Since y= (r*k*t^2)/2
k_tuned =130;           % Tunned value for K

Gp_s_1=k_1/(s*s);           % Continuous Model transfer function Gp(s)
Gp_s=k_tuned/(s*s);


% Graph: -------------------
hold on
plot(time_sec, angle,'b');   % Experimental data
step(0.4*Gp_s_1,'--m')        % Step at 40% Dutycycle (0.4) [Raw model]
step(0.4*Gp_s,'g',8)          % Tuned Model

legend('Experimental data', 'Continous Model (first guess)', 'Cotinuous Model (tunned)')
grid on

%% Discretize (Bilinear Transform)
z=tf('z',1e-3);
Ts=1e-3;                      % Sampling Period
Gp_z=c2d(Gp_s,Ts,'tustin');   % Discrete Model Gp(z)
close all

hold on
plot(time_ms, angle,'b');   % Experimental data
step(0.4*Gp_s)              % Step in the continuous model
step(0.4*Gp_z, '--r')       % Step in the discrete Model
legend('Experimental data', 'Continous Model', 'Discrete Model')
grid on


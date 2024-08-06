%% Grey Box Model of the Cubesat
clc
clear
s=tf('s');

% Experimental x Continuous Model
% Import Experimental data [Already processed]
load("Experimental_data_Dc_50\AngleZ_data.mat");
load("Experimental_data_Dc_50\DutyC_data.mat");
load("Experimental_data_Dc_50\time_sec.mat");

time_sec=time_sec(1:225);
angle=angle(1:225);
Dc=Dc(1:225);

% Plot
hold on

% Plot 1
subplot(2,1,1)
plot(time_sec, angle);       % Response
grid on
legend('DutyCycle (Input)')
xlabel('time (s)')
ylabel('Angle (Degrees)')

% Plot 2
subplot(2,1,2)
plot(time_sec, Dc);          % Input (Step from 0 to 0.4)
grid on
legend('Angle (Response)')
xlabel('time (s)')
ylabel('Duty Cycle')

%% COMPARE MODEL
% Continuous Model
y1=angle(100);
t1=time_sec(100);

k_1 = y1*2/(t1*t1*0.5);     % Since y= (r*k*t^2)/2
k_tuned =130;           % Tunned value for K
% k_tuned=91;

Gp_s_1=k_1/(s*s);           % Continuous Model transfer function Gp(s)
Gp_s=k_tuned/(s*s);


% Graph: -------------------
hold on
plot(time_sec, angle,'b');   % Experimental data
step(0.5*Gp_s_1,'--m',time_sec(end))        % Step at 40% Dutycycle (0.4) [Raw model]
step(0.5*Gp_s,'g',time_sec(end))          % Tuned Model

legend('Experimental data', 'Continous Model (first guess)', 'Cotinuous Model (tunned)', ...
    Location='north')
grid on

%% Discretize (Bilinear Transform)
z=tf('z',1e-3);
Ts=1e-3;                        % Sampling Period
Gp_z=c2d(Gp_s,Ts,'tustin');     % Discrete Model Gp(z)
close all

hold on
plot(time_sec, angle,'b');      % Experimental data
step(0.5*Gp_s,time_sec(end))               % Step in the continuous model
step(0.5*Gp_z, '--r',time_sec(end))        % Step in the discrete Model
legend('Experimental data', 'Continous Model', 'Discrete Model', Location='north')
grid on


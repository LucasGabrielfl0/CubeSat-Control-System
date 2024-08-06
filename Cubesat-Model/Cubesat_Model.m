%% Grey Box Model of the Cubesat
clc
clear
s=tf('s');

% Experimental x Continuous Model
% Import Experimental data [Already processed]
load("ExperimentalData\Response_angle.mat");
load("ExperimentalData\time_sec.mat");

% Step value (from the experimental data)
Dc_step = 0.4;
Dc_input=Dc_step*ones(size(time_sec));

% Plot ===================
hold on

% Plot 1: Angle
subplot(2,1,1)
plot(time_sec, Response_angle);          % Step Response

grid on
legend('Angle (Response)')
xlabel('time (s)')
ylabel('Angle (Degrees)')

% Plot 2: Dc (Control Signal)
subplot(2,1,2)
plot(time_sec, Dc_input);             % Step Input (0 to 0.4)

grid on
legend('DutyCycle (Input)')
xlabel('time (s)')
ylabel('Duty Cycle')

%% COMPARE MODEL
% Continuous Model
y1 = Response_angle(300);
t1 = time_sec(300);

% Gain
k_1     = y1*2/(t1*t1*Dc_step);     % Since y= (r*k*t^2)/2
k_tuned = 120;                      % Tunned value for K

% Models
Gp_s_1 = k_1/(s*s);             % First Guess
Gp_s   = k_tuned/(s*s);         % Tuned Model


% Graph: -------------------
hold on
plot(time_sec, Response_angle,'b');         % Experimental data
step(Dc_step*Gp_s_1,'--m',time_sec(end))    % Step at 40% Dutycycle (0.4) [Raw model]
step(Dc_step*Gp_s,'g',time_sec(end))        % Tuned Model

legend('Experimental data', 'Continous Model (first guess)', 'Cotinuous Model (tunned)', ...
    Location='north')
grid on

%% Discretize (Bilinear Transform)
Ts=1e-3;                        % Sampling Period
Gp_z=c2d(Gp_s,Ts,'tustin');     % Discrete Model Gp(z)

% Plot:
close all
hold on

plot(time_sec, Response_angle,'b');             % Experimental data
step(Dc_step*Gp_s,time_sec(end))                % Step in the continuous model
step(Dc_step*Gp_z, '--r',time_sec(end))         % Step in the discrete Model

legend('Experimental data', 'Continous Model', 'Discrete Model', Location='north')
grid on


%% Attitude Control: Single Loop Controller
% 1. Steady State Error = 0
% 2. Settling time: [1s < Ts(5%) < 2s]
% 3. Maximum Overshoot: Mp% =< 5%
clc
clear
s=tf('s');      % Continuous
z=tf('z',1e-3); % Discrete (Tsp= 1ms)
Ts=1e-3;

%% Gains
Kp=6.8246;
Ki=0;
Kd=11.2146;
Tf=0.00077877;

%% Plant Model (s)
% Systems Plant [Model]
Gp_s=1/(s*s);

% S-Domain Controller
Gc_s= Kp + (Ki/s) + ( Kd*s/(Tf*s +1) );

% Print info
CLTF_s=feedback(Gp_s*Gc_s,1);
stepinfo(CLTF_s)

% Plot
step(CLTF_s)
grid on

%% Z-Domain Controller
% Systems Plant [Model]
Gp_z=c2d(Gp_s,Ts,'tustin');

% Z-Domain Controller
Gc_z=c2d(Gc_s,Ts,'tustin');

% Print info
CLTF_z=feedback(Gp_z*Gc_z,1);
stepinfo(CLTF_z)

% Plot
step(CLTF_z)
grid on

%% Compare:
close all
hold on
step(CLTF_s,6)          % Step in the continuous model
step(CLTF_z, '-r',6)    % Step in the discrete Model
legend('Continous Model', 'Discrete Model')
grid on
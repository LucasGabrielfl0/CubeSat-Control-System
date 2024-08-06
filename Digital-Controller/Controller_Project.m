%% Attitude Control: Single Loop Controller
% 1. Steady State Error = 0
% 2. Settling time: [1s < Ts(5%) < 2s]
% 3. Maximum Overshoot: Mp% =< 5%
clc
clear
s=tf('s');      % Continuous
z=tf('z',1e-3); % Discrete (Tsp= 1ms)
Ts=1e-3;

% Plant Model (s)
Gp_s=tf(120,[1 0 0]);
step(0.5*Gp_s,2);
grid on

%% S-Domain Controller
% Controller (s)

%% PDF:
% Original Controller
Kp=0.0001;
Ki=0;
Kd=0.013;
Tf=0.02;

% [SATURATED] Controller:
Kp=1.3;
Ki=0;
Kd=0.9;
Tf=0.2;

Gc_s= Kp + ( Kd*s/(Tf*s +1) );

% Print info
CLTF_s=feedback(Gp_s*Gc_s,1);
ControlSignal_s=feedback(Gc_s,Gp_s);

% Display
Step_Info=stepinfo(CLTF_s,"SettlingTimeThreshold",0.05);
msg= ['[s-Domain Reponse]: ' ...
'Ts(5%)= ',num2str(Step_Info.SettlingTime),' sec | Mp% = ',num2str(Step_Info.Overshoot),'%'];
disp(msg)

% Plot
% Response
subplot(2,1,1)
step(90*CLTF_s)
grid on
legend('Response')

% Control Signal
subplot(2,1,2)
step(90*ControlSignal_s);
grid on
legend('Control Signal')

clear Step_Info msg

%% Z-Domain Closed Loop Control
% Plant Model (z)
Gp_z=c2d(Gp_s,Ts,'tustin');

% Z-Domain Controller
Gc_z=c2d(Gc_s,Ts,'tustin');

% Print info
CLTF_z=feedback(Gp_z*Gc_z,1);
ControlSignal_z=feedback(Gc_z,Gp_z);

% Display
Step_Info=stepinfo(CLTF_z,"SettlingTimeThreshold",0.05);
msg= ['[z-Domain Reponse]: ' ...
'Ts(5%)= ',num2str(Step_Info.SettlingTime),' sec | Mp% = ',num2str(Step_Info.Overshoot),'%'];
disp(msg)
% Plot
step(CLTF_z)
grid on

clear Step_Info Mp Tset msg
%% Compare:
close all

% Response
subplot(2,1,1)
hold on
step(90*CLTF_s,6)              % Step in the continuous model
step(90*CLTF_z, '--r',6)       % Step in the discrete Model
grid on
legend('Response [s]', 'Response [z]', Location='southeast')



% Control Signal
subplot(2,1,2)
hold on
step(90*ControlSignal_s)              % Step in the continuous model
step(90*ControlSignal_z, '--r')       % Step in the discrete Model
grid on
legend('Control Signal [s]', 'Control Signal [z]')
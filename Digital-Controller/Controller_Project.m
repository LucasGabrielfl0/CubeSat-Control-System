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
Gp_s=1/(s*s);

%% S-Domain Controller
% Controller (s)
% %% PID
% % Gc_s= Kp + (Ki/s) + ( Kd*s );

% % PIDF
% Kp=0.015;
% Kp=2;
% Ki=0;
% Kd=1.85;
% Tf=0.23;
% Tf=0.3;
% Tf=0000000.1;
% Gc_s= Kp + (Ki/s) + ( Kd*s/(Tf*s +1) );


%% PD
% Kp=0.04;
% Kd=1.8;
% Tf=0.00001;
% Kp=1.7499;
% Kd=9.9985;
% Gc_s= Kp + ( Kd*s );
% Gc_s=Kp + ( Kd*s/(Tf*s +1) );

%% PDF:
% Kp=0.026425;
% Kd=1.7377;
% Tf=0.0050352;

% Kp=0.1;
% Kd=1.4;
% % Tf=0.04;

% Kp=0.02;
% Kp=0.1;
% Kd=1.66;
% Kd=1.4;
% Tf=0.005;

% Kp=1.5959;
% Kd=9.5485;
Tf=0.00001;
Gc_s=Kp + ( Kd*s/(Tf*s +1) );


gain=110;
Gc_s=Gc_s/gain;
Gp_s=Gp_s*gain;

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


% Gc_test=Kp+ Ki*Ts*(z+1)/(2*(z-1)) + Kd*2*(z-1)/(Ts*(z+1));
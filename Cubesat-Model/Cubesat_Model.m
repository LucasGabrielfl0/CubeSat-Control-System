%% Grey Box Model of the Cubesat
clc
clear
s=tf('s');

%% Experimental x Continuous Model
% Import Experimental data

% Continuous Model
J=1;                % Moment of Inertia
Gp_s=1/(J*s*s);     % Continuous Model transfer function Gp(s)

% Graph: -------------------
hold on
step(0.2*Gp_s)      % Step at 20% Dutycycle

legend('Experimental data', 'Continous Model')

%% Discretize (Bilinear Transform)
Ts=1e-3;                      % Sampling Period
Gp_z=c2d(Gp_s,Ts,'tustin');   % Discrete Model Gp(z)

hold on
step(0.2*Gp_s)          % Step in the continuous model
step(0.2*Gp_z, '-r')    % Step in the discrete Model
legend('Experimental data', 'Continous Model', 'Discrete Model')
grid on


%% Compare Model x System
% legend('Continous Model', 'Discrete Model')
% Experimental Data
% Continuous (s) Model Response
% Discrete (z) Model Response

% legend('Experimental data', 'Continous Model', 'Discrete Model')



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

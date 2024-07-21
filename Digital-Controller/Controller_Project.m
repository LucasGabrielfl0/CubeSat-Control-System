%% Attitude Control: Single Loop Controller
% 1. Steady State Error = 0
% 2. Settling time: [1s < Ts(5%) < 2s]
% 3. Maximum Overshoot: Mp% =< 5%
clc
clear
s=tf('s');

a1=readmatrix('Experimental_data\Data.csv');
a1=-a1;
time=0:1:4524;
time=reshape(time,4525,1);

plot(time, a1)
% T = 1 ms, Ts= 1.5s
% Systems Plant [Model]

% S-Domain Controller

% Closed Loop Response (s)

%% Z-Domain Controller
Tsp=1e-3;

z=tf('z',Tsp);


% Closed Loop Response (Z)
% hold on

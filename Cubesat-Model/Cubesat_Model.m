%% Grey Box Model of the Cubesat
clc
clear
s=tf('s');

%
K=1;
J=1;
Cubesat=1/(J*s*s);
Cubesat1=K/(s*s);
Cubesat2=K*5/(s*s);
step(Cubesat1, Cubesat2)
legend('K=1', 'K=5')
grid on


k=1/J;

%% Import Experimental Step response

%% Model Response

%% Compare Model x System
% y= a*t
% (K/s^3) => K(t^2)/2
% a=K/2 => K=2*a
close all
y1=9e5;
t1=601;
a= y1/(t1*t1);
k2=2*a;
t=0:1:900;
yt=a*t.*t;
hold on
plot(t,yt, 'g--')
step(Cubesat2)
grid on
legend('Model', 'Plant')
disp(k2)
% grid on

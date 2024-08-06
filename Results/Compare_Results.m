%% Comparing Result
% Comparing Results from Simulink and experimental tests
clc
clear

%% Experimental tests:
load('ExperimentalData_180.mat')        % Experimental data

% Plot
hold on
plot(time_sec_180,Response_angle_180)
plot(time_sec_180,Setpoint_angle_180)
legend('Response', 'Setpoint')

grid on

%% Simulink Tests:
load('SimulinklData_180.mat')

plot(sim_time, sim_Response)                % Simulated response

xlabel('time (s)')
ylabel('Angle (degrees)')
title('Step Response')
grid on

%% Compare
close all
% Plot
hold on
plot(time_sec_180, Response_angle_180)      % Experimental response
plot(time_sec_180, Setpoint_angle_180)      % Setpoint              
plot(sim_time, sim_Response)                % Simulated response
xlabel('time (s)')
ylabel('Angle (degrees)')
title('Step Response')
legend('Experimental response', 'Simulink Response', 'reference')
grid on
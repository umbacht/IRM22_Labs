%tabula rasa
clear,clf,close all

%import position data and size
A = importdata('pos_logfile.csv');
x_raw = A.data(:,1);
y_raw = A.data(:,2);
n = size(A.data,1);

%create time axis given sampling time
dt = 1 / 60; %s
t = linspace(0,n*dt,n);

%plot overview
figure('Name','Full Data Range')
plot(t,x_raw,t,y_raw);
title('Position Trajectory')
xlabel('t [s]')
ylabel('[mm]')
legend('x','y');
grid on

%choose interesting time range
t_start = 5; %s
t_end = 20; %s

%clip data to time range
i_start = find(t > t_start, 1, 'first' );
i_end = find(t < t_end, 1, 'last');
t = t(i_start:i_end);
x_raw = x_raw(i_start:i_end);
y_raw = y_raw(i_start:i_end);

%plot again
figure('Name','Clipped Range')
plot(t,x_raw,t,y_raw)
title('Clipped Position Trajectory')
xlabel('t [s]')
ylabel('[mm]')
legend('x','y');
grid on

%% Q1:
%TODO : Compute the x-velocity using the Euler backward method.
%Check out the Matlab function diff() and pay attention to the
%size of the output array. What would be a sensible value to use
%for the first value of the difference array?

% Your code here

%% Q2:
%TODO: Filter the position values using the moving average method.

%%Hint 1: Matlab provides the function movmean() for this, but make sure that
%you use it in the right way! The first example in the documentation is 
%not what you need, since our controller cannot see into the future. 

%Hint 2: finddelay(x,y) estimates the delay between two signals in frames.

% Your code here



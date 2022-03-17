close all;
clear;

%% PreLab 03
%This was in silvans code: 
opts = bodeoptions;
opts.FreqUnits = 'Hz';

%Hz to rad/s

H = tf([1], [1/100 1]);

figure(1)
subplot(4,1,1:2)
bodeplot(H, opts)
%bode(H)
grid on

subplot(4,1,3)
impulse(H)
grid on

subplot(4,1,4)
step(H)
grid on

close all;
clear;

%% PreLab 03
opts = bodeoptions;
opts.FreqUnits = 'Hz';

%Hz to rad/s

H = tf([1], [1/(2*pi*100) 1]);

figure(1)
subplot(4,1,1:2)
bodeplot(H, opts)
grid on

subplot(4,1,3)
impulse(H)
grid on

subplot(4,1,4)
step(H)
grid on

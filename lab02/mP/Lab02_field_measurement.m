close all
clear

data = readmatrix("Measurements/field_strength_3.txt");
field = flip(data(1:end,1))./1000;
distance = (0:2:28)'./1000;
z = distance;

R = 0.02; % Radius of magnet
D = 0.01; % Thickness of magnet

fun = @(Br,z) Br/2*((D+z)./(sqrt(R^2+(D+z).^2))-z./sqrt(R^2+z.^2));

x0 = 0.1756;
Br = lsqcurvefit(fun, x0, distance, field);

approx_field = fun(Br, distance);

figure(1)
plot(distance, field, 'x')
hold on
plot(distance, approx_field, 'r')

xlabel('Distance [m]');
ylabel('Magnetic Field [T]');
title('2.3.4.4 Magnetic Fieldstrength');

hold off
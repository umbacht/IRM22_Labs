close all;
clear all;

data = readmatrix("voltage_data1.txt");
raw = data(1:end,1);

mean_raw = mean(raw);
standad_deviation = std(raw);

figure(1);
plot(data);
hold on

yline(mean_raw,'red');
yline(mean_raw+standad_deviation,'green');
yline(mean_raw-standad_deviation, 'green');
xlabel('Sample n');
ylabel('Volts [V]');
title('2.3.3.2 Hall sensor voltage output');
legend('Data', 'Mean', '+Standard deviation', '-Standard deviation');
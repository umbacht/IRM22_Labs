close all;
clear all;

%% 2.3.3.2
data = readmatrix("Measurements/voltage_data1.txt");
raw = data(1:end,1);

mean_raw = mean(raw);
standad_deviation = std(raw);
disp("Mean: ");
disp(mean_raw);
disp("Standard Deviation: ");
disp(standad_deviation);

figure(1);
plot(data);
hold on

yline(mean_raw,'red');
yline(mean_raw+standad_deviation,'--green');
yline(mean_raw-standad_deviation, '--green');
xlabel('Samples');
ylabel('Volts [V]');
title('2.3.3.2 Hall sensor voltage output - Non averaged');
legend('Data', 'Mean', '+ Standard deviation', '- Standard deviation');
hold off

%% 2.3.3.3
data = readmatrix("Measurements/voltage_data_averaged20.txt");
raw = data(1:end,1);

mean_raw = mean(raw);
standad_deviation = std(raw);
disp("Mean: ");
disp(mean_raw);
disp("Standard Deviation: ");
disp(standad_deviation);

figure(2);
plot(data);
hold on

yline(mean_raw,'red');
yline(mean_raw+standad_deviation,'--green');
yline(mean_raw-standad_deviation, '--green');
xlabel('Samples');
ylabel('Volts [V]');
title('2.3.3.3 Hall sensor voltage output - 20 Average');
legend('Data', 'Mean', '+ Standard deviation', '- Standard deviation');
hold off

%% 2.3.3.3
data = readmatrix("Measurements/voltage_data_averaged200.txt");
raw = data(1:end,1);

mean_raw = mean(raw);
standad_deviation = std(raw);
disp("Mean: ");
disp(mean_raw);
disp("Standard Deviation: ");
disp(standad_deviation);

figure(3);
plot(data);
hold on

yline(mean_raw,'red');
yline(mean_raw+standad_deviation,'--green');
yline(mean_raw-standad_deviation, '--green');
xlabel('Samples');
ylabel('Volts [V]');
title('2.3.3.3 Hall sensor voltage output - 200 Average');
legend('Data', 'Mean', '+ Standard deviation', '- Standard deviation');
hold off



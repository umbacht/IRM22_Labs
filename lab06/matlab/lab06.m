
%% PreLab 06

%%%%%%%%%%%%%%%%%%%%
% global variables %
%%%%%%%%%%%%%%%%%%%%

%create time variable, goes from 0 to 5 sec in 0.0001 steps
timestep=0.0001;
t=0:timestep:5;

%%%%%%%%%%%%%
% Prelab Q1 %
%%%%%%%%%%%%%

 
% Differential Equation of the sytem: x''(t) = 30/5*theta(t)
% create the transfer function of the system (you should use the tf() function):
P = tf(6, [1, 0, 0]);


% set step options to have a step-size of 0.1 instead of 1 (standard), use
% stepDataOptions()
opts = stepDataOptions('InputOffset',0,'StepAmplitude',0.1);


% open loop impulse and step response in one figure (two subplots):

figure('Name','Q1) Impulse- and Stepresponse of OL system');

subplot(2,1,1);
[y_impulse_OL,t] = impulse(P, t, opts);
plot(t, y_impulse_OL);
ylabel('Deviation of x from linearization point');
xlabel('Time [s]');
title('Impulse response');
grid on;

subplot(2,1,2);
[y_step_OL, t] = step(P, t, opts);
plot(t, y_step_OL);
ylabel('Deviation of x from linearization point');
xlabel('Time [s]');
title('Step response');
grid on;

disp("Prelab Q1")
disp("Impulse response: response of the OL system to a brief impulse input signal.")
disp("The brief impulse sets the ball in motion. After that impulse, the plate is in its original (non tilted) position again, however, the ball" + ...
    "keeps on rolling given the initial impulse for movement. As the system will not converge to 0, it is unstable.")
disp("Step response: response of the OL system as reaction to a step signal on the input.")
disp("By setting a step input, the system reacts by tilting the plate to move the ball. " + ...
    "Without feedback however, the system will not track the position of the ball and just remain in its tilted position. " + ...
    "This leads to a continuous acceleration of the ball. Also under the step input the system is unstable as it does not converge to 0.")



%%%%%%%%%%%%%
% Prelab Q2 %
%%%%%%%%%%%%%

% Controller Parameters:
Kp=20;
Ki=1;
Kd=2;
Kd_=20;

% create the transfer function of the Controller:
C_pid = pid(Kp,Ki,Kd);
C_pid_20 = pid(Kp,Ki,Kd_);

% create the transfer function of the feedback loop
H = feedback(P * C_pid, 1);
H_20 = feedback(P * C_pid_20, 1);

% Plot the closed loop step response
figure('Name','Prelab Q-2 Stepresponse of CL system');

subplot(2,2,1)
[y, x] = step(H, opts);
plot(x, y)
ylabel('Deviation of x from linearization point');
xlabel('Time [s]');
title('Step response with Kd=2');
grid on

subplot(2,2,2)
[y, x] = step(H_20, opts);
plot(x, y)
ylabel('Deviation of x from linearization point');
xlabel('Time [s]');
title('Step response with Kd=20');
grid on

subplot(2,2,3)
[y_step_CL, t] = step(H, t, opts);
plot(t, y_step_CL);
ylabel('Deviation of x from linearization point');
xlabel('Time [s]');
title('Step response with Kd=2 - 5s plot');
grid on

subplot(2,2,4)
[y_step_CL_20, t] = step(H_20, t, opts);
plot(t, y_step_CL_20);
ylabel('Deviation of x from linearization point');
xlabel('Time [s]');
title('Step response with Kd=20 - 5s plot');
grid on

disp("Prelab Q2")
disp("The response for the case Kd=2 is underdamped. By increasing Kd, the system is damped " + ...
    "more heavily and reacts slower to the input. ")
disp("Considering the real system, by increasing the gain Kd the system could become too slow. " + ...
    "As the object tracking by the pixy cam also introduces a delay in the system, it might be too slow " + ...
    "to control the movement of the ball and become instable.")
disp("")

%%%%%%%%%%%%%
% Prelab Q3 %
%%%%%%%%%%%%%

% controller constants:
Kp=1.7;
Ki=0.1;
Kd=0.6;

% create the transfer function of the Controller 
C_pid_delay = pid(Kp,Ki,Kd);

% Variables for delay:
delay=0.08; % 80ms
delay_= 1; % 1s %if you want to test with 1 sec delay

% create the transfer function of the delay in the system
tf_delay = tf(1, [0, 0, 1],'InputDelay',delay);

% create the transfer function of the feedback loop with delay
H_delay = feedback(tf_delay * P * C_pid_delay, 1);


% Plot the closed loop step response of the system with delay
figure('Name','Prelab Q-3 Stepresponse of CL system with time delay')
[y, t] = step(H_delay, 5, opts);
plot(t, y)
grid on
ylabel('Deviation of x from linearization point');
xlabel('Time [s]');
title("CL Step response with time delay")

% check and print design criteria for "steady state" error at 5 seconds
Steady_State_error_at_t_5s = abs(0.1 - y(end))


disp("Prelab Q3")
disp("The system will become more unstable and therefore more difficult to control with " + ...
    "higher time delays. The position of the ball is measured at a time t, processed, and fed " + ...
    "to the controller with a delay dt. This means that the system at time t will base its control on" + ...
    "the position of the ball at time t-dt instead of t. Meaning that the system will most likely assume an " + ...
    "outdated position of the ball for its control.")


%%%%%%%%%%%%%
% Prelab Q4 %
%%%%%%%%%%%%%

disp("Prelab Q4")
disp("The motor saturation can lead to an integrator wind-up. By having too high a set point" + ...
    "that the system can physically not follow, the integral error term will increase. Due to that" + ...
    "the system can overshoot and continue to accumulate its error continuously over time. ")






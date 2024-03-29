#include <stdio.h>
#include "util.h"

int main(){
  //////////////////////////////
  /////// Initialization ///////
  //////////////////////////////

  //Time information
  time_t rawtime;
  struct tm *info;
  char buffer[80];
  time(&rawtime);
  info = localtime(&rawtime);
  printf("Formatted date & time : |%s|\n", buffer );

  //Print Welcome Message
  printf("\e[1;1H\e[2J"); // Clear screen
  printf("#####################\n");
  printf("Ball and Plate System\n");
  printf("#####################\n");
  printf("|%s|\n", buffer );
  printf("\n");
  printf("Opening serial port...\n");

  // Initialize the serial port
  const char* port= "/dev/cu.SLAB_USBtoUART";
  int fd = serialport_init(port, 115200);
  if (fd == -1){
      printf("Could not open the port.\n");
      printf(" - Is the Arduino IDE terminal opened?\n");
      printf(" - Is the device connected to the VM?\n");
      return -1;    
  }

  // Initialize robot and check
  // if messages are received
  initBallBalancingRobot(fd);

  // Make sure that serial port is relaxed
  usleep(20*1000);

  // Parameter loading functions
  load_parameters();
  load_servo();

  //////////////////////////////
  //////// Task Selection //////
  //////////////////////////////
  int task_selection = 0;
  printf("Select Task: ");
  scanf("%d", &task_selection);

  //////////////////////////////
  /////////// Task 1 ///////////
  //////////////////////////////

  if(task_selection == 1){
      /* Test inverse kinematics via
      terminal */
        
      //initalize variables:
      double plate_angles[] = {0,0};
      double servo_angles[] = {0,0,0};

      int again = 1;

      while(again==1){
        printf("Give me Phi and Theta:\n");
        scanf("%lf%lf", &plate_angles[0], &plate_angles[1]);
        if(inverseKinematics(plate_angles, servo_angles)==0){
          printf("Phi: %f, Theta: %f, A: %f, B: %f, C: %f\n", plate_angles[0], plate_angles[1], servo_angles[0], servo_angles[1], servo_angles[2]);
          servoCommand(fd, servo_angles);
        }else{
        printf("Out of bounds");
        }
        printf("Again? 1: Yes, 2: No\n");
        scanf("%i",&again);
      }
    }

  //////////////////////////////
  /////////// Task 2 ///////////
  //////////////////////////////
  /*Test camera calibration*/
  if(task_selection == 2){
      
      //initalize variables:
      int x;
      int y;
      double x_w;
      double y_w;
      int pixy_return_value;
      int flag_2;
      
        // read ball position
        flag_2 = readFromPixy(fd, &pixy_return_value, &x, &y);
        if (flag_2 == -1) {
            printf("Pixy Error occurred\n");
            return 0;
        }
        if (pixy_return_value == 0) {
            printf("OBJECT NOT DETECTED\n");
        }

        // to world frame
        cameraCalibration(x, y, &x_w, & y_w);
        printf("x_pixy: %i, y_pixy: %i\nx_w: %lf, y_W: %lf\n", x, y, x_w, y_w);

  }

  //////////////////////////////
  /////// Task 4/5/6 ///////////
  //////////////////////////////

  if ((task_selection == 4) || (task_selection == 5) || (task_selection == 6)) {

    //TODO: Initialize default PID parameters
    double k_p = 0.07;
    double k_i = 0.03; 
    double k_d = 0.03;

    //TODO: Intialize filter window size
    int n_pos = 20;
    int n_vel = 5;

    // TODO: Ask for user input to change PID parameters
      /* ********************* */
      /* Insert your Code here */
      /* ********************* */
    
    int default_pid = 0;
    printf("PID Controler, use default parameters? (1: Yes, 0: No)\n");
    scanf("%i",&default_pid);
    
    if (!default_pid){
      printf("Enter PID parameters: P I D\n");
      scanf("%lf %lf %lf",&k_p, &k_i, &k_d);
    }

    // Variables for Pixy2
    int flag = 0;       //flag that detects if the pixy cam can detect a ball
    int x_px = 0;       //raw x coordinate read by pixy cam
    int y_px = 0;       //raw y coordinate read by pixy cam
    double x_cal = 0;   //calibrated x coordinate in plate frame and mm
    double y_cal = 0;   //calibrated y coordinate in plate frame and mm
    double x_filt = 0;  //filtered x coordinate in plate frame and mm
    double y_filt = 0;  //filtered y coordinate in plate frame and mm
    double vel_x = 0;   //x velocity calculated from filtered position
    double vel_y = 0;   //y velocity calculated from filtered position

    //read pixy a couple of times to clear buffer
    for(int i = 0; i < 20; i++){
      readFromPixy(fd, &flag, &x_px, &y_px);
    }
    
    // create buffer arrays for filtered variables
    // [0] is always the current element
    // make sure buf_size is bigger than filter windows
    int buf_size = 50;
    double x_raw[buf_size];  // calibrated, unfiltered
    double y_raw[buf_size];
    double vx_raw[buf_size];  // 1st order derivative
    double vy_raw[buf_size];
    double x[buf_size];  // filtered position
    double y[buf_size];
    double vx[buf_size];  // filtered velocity
    double vy[buf_size];

    // initialize buffer arrays to zero
    for (int i = 0; i < buf_size; i++) {
      x_raw[i] = 0;
      y_raw[i] = 0;
      vx_raw[i] = 0;
      vy_raw[i] = 0;
      x[i] = 0;
      y[i] = 0;
      vx[i] = 0;
      vy[i] = 0;
    }

    // initialize angles
    double servo_angles[] = {0,0,0};
    double plate_angles[] = {0,0};

    // reference variables for control
    // are being set in reference functions
    double x_ref, y_ref, vx_ref, vy_ref;

    // pid variables
    double x_integ = 0;
    double y_integ = 0;
    double u_x = 0;
    double u_y = 0;
    double e_x = 0;
    double e_y = 0;
    double integ_windup_limit = 100;
    //Logfile with datetime as filename
    char datetime[80];
    strftime(datetime,80,"%Y-%m-%d_%H-%M-%S_pid_log.txt", info);
    FILE *fp = fopen(datetime, "w+");
    startLogging(fp, task_selection, k_p, k_d, k_i, n_pos, n_vel);

    //Timing variables
    // TODO: Measure the current sampling time dt (in seconds, for the derivative): It is the time it takes to run the previous loop iteration.
    // Hint: use getMicroseconds() and don't forget to convert to seconds.
      long start = 0;
      long end = 16;
      long t0 = getMicroseconds();  //get starting time of the loop
      double dt = 0.016; //variable for timing
      double current_time = 0;

    while(1){
    
        /* ********************* */
        /* Insert your Code here */
        /* ********************* */
      //TODO: Get current sampling time dt
      dt = (end - start)/1000000.0;
      start = getMicroseconds();

      //TODO: Get the coordinates of the ball in the Pixy Camera frame (Use a function in util.c)
      flag = readFromPixy(fd, &flag, &x_px, &y_px);
      //If anything is detected, enter if-bracket
      if(flag){
        //TODO: Use camera calibration form Lab05
        cameraCalibration(x_px, y_px, &x_cal, &y_cal);
        //TODO: Place measurements in buffer array
        pushBack(x_cal, x_raw, buf_size);
        pushBack(y_cal, y_raw, buf_size);

        //Hint: There is a function called pushBack
        // in util.h that you can use here.

        //TODO: Apply filter to position coordinates
        x_filt = movingAverage(n_pos, x_raw);
        y_filt = movingAverage(n_pos, y_raw);
        pushBack(x_filt, x, buf_size);      
        pushBack(y_filt, y, buf_size); 
        //TODO: Compute velocity
        vel_x = (x[0]-x[1])/dt;
        vel_y = (y[0]-y[1])/dt;

        //TODO: Place velocity in buffer array (use pushBack function)
        pushBack(vel_x, vx_raw, buf_size); 
        pushBack(vel_y, vy_raw, buf_size);              
        //TODO: Apply filter to velocity
        pushBack(movingAverage(n_vel, vx_raw), vx, buf_size);  
        pushBack(movingAverage(n_vel, vy_raw), vy, buf_size);       

        //TODO: Set reference depending on task
        switch(task_selection){
          case 4: x_ref = 0;
                  y_ref = 0; 
                  vx_ref = 0; 
                  vy_ref = 0; /*TODO: Postlab Q4 centering task */ 
                  break;
          case 5: stepResponse(current_time, &x_ref, &y_ref, &vx_ref, &vy_ref);
                  /*TODO: Postlab Q5 step response reference  --> use function in util.h */
                  break;
          case 6: circularTrajectory(current_time,&x_ref, &y_ref, &vx_ref, &vy_ref);
                  /*TODO: Postlab Q6 circular trajectory reference --> implement & use function in util.h */
                  break;
        }
        e_x = x_ref - x[0];
        e_y = y_ref - y[0];

        //TODO: Update Integrator after an initial delay
        //Hint: Wait 0.5s before starting to update integrator
        if (current_time > 0.5){
          x_integ += e_x * dt;
          y_integ += e_y * dt;

          if (x_integ >= integ_windup_limit){
            x_integ = integ_windup_limit;
          } else if (x_integ <= -integ_windup_limit)
          {
            x_integ = -integ_windup_limit;
          }
          if (y_integ >= integ_windup_limit){
            y_integ = integ_windup_limit;
          } else if (y_integ <= -integ_windup_limit)
          {
            y_integ = -integ_windup_limit;
          }
          
        }

        //TODO: Compute PID (remember, PID output is the plate angles)
        u_x = k_p * e_x + k_d * (vx_ref - vx[0]) + k_i * x_integ;
        u_y = k_p * e_y + k_d * (vy_ref - vy[0]) + k_i * y_integ;        
        //TODO: Define Plate angles from PID output (watch out for correct sign)
        plate_angles[0] = -u_y;
        plate_angles[1] = u_x;

        //TODO: Compute servo angles and send command
        inverseKinematics(plate_angles, servo_angles);
        servoCommand(fd, servo_angles);

        end = getMicroseconds();
        current_time += dt;

        //Open logging file and log everything to textfile
        fp = fopen(datetime, "a");

        logger(fp, end, current_time, dt, k_p, k_d, k_i, x_ref, y_ref, vx_ref,
               vy_ref, x_raw[0], y_raw[0], x[0], y[0], vx_raw[0], vy_raw[0],
               vx[0], vy[0], plate_angles, servo_angles, x_integ, y_integ);
      }
    }
  }

  return 0;
}

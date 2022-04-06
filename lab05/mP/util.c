#include "util.h"
#include <math.h>

int initBallBalancingRobot(int fd) {
  
  printf("\e[1;1H\e[2J"); // Clear screen
  printf("#######################\n");
  printf("Hardware Initialization\n");
  printf("#######################\n");

  // Let feather reboot
  usleep(200);

  // Check pixy readings
  int pixy_return, flag, x, y;
  pixy_return = readFromPixy(fd, &flag, &x, &y);
  while (!pixy_return) {
    // retry until connection established
    pixy_return = readFromPixy(fd, &flag, &x, &y);
  }
  
  printf("%s, x = %d, y = %d \n", "INIT: Pixy Coordinates received", x, y);

  // Do some inverse kinematics to check for errors
  double position[] = {0, 0, 130};
  double plate_angles[] = {0, 0};
  double servo_angles[] = {0, 0, 0};
  inverseKinematics(plate_angles, servo_angles);
  printf("INIT: Inverse Kinematics initialized\n");
  printf("INIT: Finished\n");
  // printf("INIT: A: %.2f, B: %.2f, C: %.2f
  // \n",servo_angles[0],servo_angles[1],servo_angles[2]);

  tcflush(fd, TCIFLUSH);

  // Send motor commands
  // servoCommand(fd,servo_angles);

  return 1;
}

int inverseKinematics(const double* plate_angles, double* servo_angles) {

  // Load parameters R, L_1, L_2, P_z etc. from parameters file. Example: double R = bbs.R_plate_joint;
  // Then implement inverse kinematics similar to prelab

  
  // Function to compute servo angles from the plate angles. Takes 2 pointers as input

  float L1 = bbs.l1;            //Length of Segment 1 in mm
  float L2 = bbs.l2;           //Length of Segment 2 in mm
  float P_z = bbs.plate_height;          //Height of Plate center in mm
  float R = bbs.R_plate_joint;            //Distance from Plate center to anchor points A,B and C in mm
  float beta[3];            //Initialize array to store beta servo angles
  
  /*--------------------------------------------------------------------------
  Transform plate angles from degrees to radians for calculation
  --------------------------------------------------------------------------*/
  float plate_angles_rad[2];
  plate_angles_rad[0] = plate_angles[0]*M_PI/180;
  plate_angles_rad[1] = plate_angles[1]*M_PI/180;
  
  /*--------------------------------------------------------------------------
  // Calculate the z-offsets of each anchor point according to the formulas
  --------------------------------------------------------------------------*/
  
  float delta_z[3];
  delta_z[0] = R*sin(plate_angles_rad[0]);
  delta_z[1] = (-0.5*R*sin(plate_angles_rad[0])+(sqrt(3)/2)*R*sin(plate_angles_rad[1]));
  delta_z[2] = (-0.5*R*sin(plate_angles_rad[0])-(sqrt(3)/2)*R*sin(plate_angles_rad[1]));
  
  /*--------------------------------------------------------------------------
  // Calculate the beta-servo angles according to the law of cosines
  --------------------------------------------------------------------------*/
  
  beta[0] = acos((pow(P_z+delta_z[0],2)+pow(L1,2)-pow(L2,2))/(2*L1*(P_z+delta_z[0])));
  beta[1] = acos((pow(P_z+delta_z[1],2)+pow(L1,2)-pow(L2,2))/(2*L1*(P_z+delta_z[1])));
  beta[2] = acos((pow(P_z+delta_z[2],2)+pow(L1,2)-pow(L2,2))/(2*L1*(P_z+delta_z[2])));
  
  /*-------------------------------------------------------------------------- 
  // Return -1 if any of the angles is not defined
  --------------------------------------------------------------------------*/ 
  
  if(isnan(beta[0])||isnan(beta[2])||isnan(beta[3])){
    return -1;
  }
  
  /*-------------------------------------------------------------------------- 
  // Calculate the alpha servo angles and transform them back to degrees
  --------------------------------------------------------------------------*/
  servo_angles[0] = (M_PI/2 - beta[0])*180/M_PI;
  servo_angles[1] = (M_PI/2 - beta[1])*180/M_PI;
  servo_angles[2] = (M_PI/2 - beta[2])*180/M_PI;
    
  return 0;
}


int cameraCalibration(const int x_in, const int y_in, double* x_out, double* y_out){

    // implement camera calibration code
    // make sure to multiply the raw pixy2 coordinates with the scaling factor (ratio between
    // image fed to matlab for calibration and pixy2 resolution): bbs.calibration_image_scale.
    
    /* ********************* */
    /* Insert your Code here */
    /* ********************* */
    
  return 0;
};




/* Sends servo angles to serial port */
int servoCommand(int fd, double* servo_angles) {
  // check serial
  int writeval;

  // assign values
  double angleA = servo_angles[0] + servo.bias_A;
  double angleB = servo_angles[1] + servo.bias_B;
  double angleC = servo_angles[2] + servo.bias_C;

  int min = servo.min_angle;
  int max = servo.max_angle;

  // check if values are valid
  int condition = (angleA < max && angleA > min) &&
                  (angleB < max && angleB > min) &&
                  (angleC < max && angleC > min);

  if (condition != 1) {
    printf("ERROR: Servo angles out of bounds.\n");
    return -1;
  }

  // assemble command
  char command[50];
  sprintf(command, "C %.2f %.2f %.2f\n", angleA, angleB, angleC);

  // Flush serial port output
  tcflush(fd, TCOFLUSH);
  // send command
  writeval = write(fd, command, strlen(command));

  return 0;
}

/* Reads pixel coordinates from Pixycam. Also returns a flag whether an object
 * was detected or not */
int readFromPixy(int fd, int* flag, int* x, int* y) {
  char buff[20];
  const char command[] = "P\n";
  int writeval;
  char* token;
  const char delim[] = " ";

  // Flush serial port input
  tcflush(fd, TCIFLUSH);
  tcflush(fd, TCOFLUSH);

  // Write command to pixy
  writeval = serialport_write(fd, command);
  usleep(10 * 1000);

  // Read until until no more bytes available
  // If not data is availabe, retry until success
  int readval = 0;
  while(readval != 1){
    readval = serialport_read_until(fd, buff, sizeof(buff), '\n', 100);
  }
  
  // printf("readFromPixy: after read \n");
  // printf("writeval = %d, readval = %d", writeval,readval);

  // Catch read write errors
  if (!readval) {
    //printf("SERIAl READ FAILED with %d \n",readval);
    return -1;
  }

  // Add terminating 0 to make string
  buff[sizeof(buff) - 1] = 0;

  // extract values using strtok
  token = strtok(buff, delim);

  // Verify initial character
  if (token[0] != 'A') {
    //printf("SERIAL HEADER ERROR: %.20s\n",buff);
    return -1;
  }

  token = strtok(NULL, delim);
  *flag = atoi(token);
  token = strtok(NULL, delim);
  token = strtok(NULL, delim);
  *x = atoi(token);
  token = strtok(NULL, delim);
  token = strtok(NULL, delim);
  *y = atoi(token);

  return 1;
}


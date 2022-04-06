#include <stdio.h>
#include "util.h"

int main(){
  //////////////////////////////
  /////// Initialization ///////
  //////////////////////////////

  //Print Welcome Message
  printf("\e[1;1H\e[2J"); // Clear screen
  printf("#####################\n");
  printf("Ball and Plate System\n");
  printf("#####################\n");
  printf("\n");
  printf("Opening serial port...\n");

  // Initialize the serial port
    const char* port= "/dev/cu.SLAB_USBtoUART";//vm: "/dev/ttyUSB0", mac: "/dev/cu.SLAB_USBtoUART"
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
  scanf("%i", &task_selection);

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
      printf("Give me Theta and Phi:");  
      scanf("%lf%lf", &plate_angles[0], &plate_angles[1]);
      if(inverseKinematics(plate_angles, servo_angles)==0){
        printf("Theta: %f, Phi: %f, A: %f, B: %f, C: %f\n", plate_angles[0], plate_angles[1], servo_angles[0], servo_angles[1], servo_angles[2]);
      }else{
      printf("Out of bounds");
      printf("Again? 1: Yes, 2: No");
      scanf("%i",&again);
      }
    }
    }
    
  //////////////////////////////
  /////////// Task 2 ///////////
  //////////////////////////////
  /*Test camera calibration*/
  if(task_selection == 2){
      
      //initalize variables:
      
    /* ********************* */
    /* Insert your Code here */
    /* ********************* */

   
  }


  return 0;
}

#include <iostream>
#include <math.h>

// Function to get the plate angles (in int)
uint16_t get_angles(){
      int temp;
      scanf("%d", &temp);
      return temp;
}

// Function to compute servo angles from the plate angles. Takes 2 pointers as input
int compute_servo_angles(float *plate_angles, float *servo_angles){
  float L1 = 42;            //Length of Segment 1 in mm
  float L2 = 100;           //Length of Segment 2 in mm
  float P_z = 100;          //Height of Plate center in mm
  float R = 113.24;         //Distance from Plate center to anchor points A,B and C in mm
  float beta[3];            //Initialize array to store beta servo angles
  
  
  /*--------------------------------------------------------------------------
  
   Transform plate angles from degrees to radians for calculation

  --------------------------------------------------------------------------*/
  plate_angles[0] = plate_angles[0] * M_PI/180;
  plate_angles[1] = plate_angles[1] * M_PI/180;
  
  
  /*--------------------------------------------------------------------------
  
  // Calculate the z-offsets of each anchor point according to the formulas
  
  --------------------------------------------------------------------------*/
  float sigma_ZA = R* sin(plate_angles[0]);
  float sigma_ZB = -0.5 * R * sin(plate_angles[0]) + (sqrt(3)/2)*R*sin(plate_angles[1]);
  float sigma_ZC = -0.5 * R * sin(plate_angles[0]) - (sqrt(3)/2)*R*sin(plate_angles[1]);
  
  
  /*--------------------------------------------------------------------------
  
  // Calculate the beta-servo angles according to the law of cosines
  
  --------------------------------------------------------------------------*/
  beta[0] = acos((pow(P_z + sigma_ZA,2) + pow(L1,2) - pow(L2, 2)) / (2 * (P_z + sigma_ZA) * L1));
  beta[1] = acos((pow(P_z + sigma_ZB,2) + pow(L1,2) - pow(L2, 2)) / (2 * (P_z + sigma_ZB) * L1));
  beta[2] = acos((pow(P_z + sigma_ZC,2) + pow(L1,2) - pow(L2, 2)) / (2 * (P_z + sigma_ZC) * L1));
  
  /*-------------------------------------------------------------------------- 
  
  // Return -1 if any of the angles is not defined
  
  --------------------------------------------------------------------------*/ 
  //according to IEE standard, comparisons involving NaN are always false. 
  //Checking for NaN in beta by comparing values to themselves which is false only in case of an NaN.
  
  if ( beta[0]!=beta[0] || beta[1]!=beta[1] || beta[2]!=beta[2]){ 
    return -1;
  }
  
  
  /*-------------------------------------------------------------------------- 
  
  // Calculate the alpha servo angles and transform them back to degrees
  
  --------------------------------------------------------------------------*/
  servo_angles[0] = (M_PI/2 - beta[0]) * 180/M_PI;
  servo_angles[1] = (M_PI/2 - beta[1]) * 180/M_PI;
  servo_angles[2] = (M_PI/2 - beta[2]) * 180/M_PI;
  
  
  return 0;
}

int main () {
  
  int function_check;     //Variable to check if compute_servo_angles function was successful
  float plate_angles[2];  //Array for 2 plate angles, [0] -> phi_x; [1] -> theta_y
  float servo_angles[3];  //Array for 3 servo angles
  
  // Use your own values for the plate angles at first to test your function before using the test runner
  //plate_angles[0] = 5;
  //plate_angles[1] = 6;
  plate_angles[0] = get_angles();    //Read in plate angle "phi_x" from test runner
  plate_angles[1] = get_angles();    //Read in plate angle "theta_y" from test runner

  
  /*-------------------------------------------------------------------------- 
  
  // Call the function compute_servo_angles with the correct arguments
  
  --------------------------------------------------------------------------*/
  function_check = compute_servo_angles(&plate_angles[0], &servo_angles[0]);


  // If successful print out the alpha angles for each servo in degrees, rounded to the 1st decimal place
  if (function_check == 0){
    printf("\nAlpha_A = %.1f°,  Alpha_B = %.1f°, Alpha_C = %.1f°\n",servo_angles[0], servo_angles[1], servo_angles[2]);
  }
  
  // If unsuccessful print error message that at least one plate angle is invalid
  if (function_check == -1){
    printf("Plate Angle Not Valid");
  }
  
}
// declaring variables
int dl, mlt, incoming;

// define an array to access the LED Pins
int led_pins[8] = {12, 27, 33, 15, 32, 14, 22, 23}; 

void setup() {
   
   // setting some initial values
   dl = 10;
   mlt = 50;
   incoming = 0;

   //_________________Begin - Part A_______________
   
   Serial.begin(115200);

   int x=0;
   for (x=0; x<8; x++){     //setting all GPIOs connected to the LED as OUTPUT pins
    pinMode(led_pins[x], OUTPUT); 
   }
   
   pinMode(21, INPUT);      //setting GPIO that is connected to the switcher as an INPUT pin.
   
   //_________________End - Part A_________________
   
}

void loop() {
   // in C, the for-loop variables need to be initialized before the loop
   // for(int i = 0; i < 9; i++) is not accepted
   
   int i=0, j=0;
   
   //_________________Begin - Part B_______________
   if( Serial.available() )
   {
     // read into variable incoming
     Serial.readBytes(((char*)&incoming),2); //in lab change this to 2 and print "incoming" below.      
     Serial.println(incoming);
     dl = incoming >> 4;
     Serial.println(dl); //dl is printed on the serial monitor
     mlt = incoming % (1<<4);
     Serial.println(mlt); //mlt is printed on the serial monitor
   }
   //_________________End - Part B_________________

   int switcher = digitalRead(21);  //reading value of de GPIO to distinguish switcher position
   if (switcher == 1){
     //_________________Begin - Part C_______________
     // loop over all output (LED) pins and set state to HIGH/LOW
     // e.g. digitalWrite(1,LOW) means you set the digital pin 1 to LOW.
     for (j =0;j<8;j++)
     {
       for (i=0;i<8;i++){
          digitalWrite(led_pins[i],LOW); 
       }
       
       digitalWrite(led_pins[j],HIGH);  
       delay(dl*mlt);
     }  
     
     delay(dl*mlt*3);
     
     //_________________End - Part C_________________
   } else {
      //_________________Begin - Part D_______________
      int arg_word_bin[8]; //empty list is initialized. 
      int n = incoming;
      int u=0;
      
      for(u = 0; u <= 7; u++)
      {
        arg_word_bin[u] = n % 2;   //binary number of incoming is stored in arg_word_bin (bin order is still inverted at this point)
            n = n / 2;
      }
      
      int q=0;
      for(q=7; q>=0; q--){
        if(arg_word_bin[q]==1){             //if the bit on a certain position in the arg_word_bin list is 1, the corresponding pin is set to HIGH. 
          digitalWrite(led_pins[q],HIGH);
        }
        else{
          digitalWrite(led_pins[q],LOW);  // all other pins are set to LOW.
        }
      }
      
      delay(10);
      //_________________End - Part D_________________
   }
   
}

// declaring variables
int dl, mlt, incoming;

// define an array to access the LED Pins
int led_pins[10] = {12, 27, 33, 15, 32, 14, 22, 23};

void setup() {
   
   // setting some initial values
   dl = 10;
   mlt = 50;
   incoming = 0;

   //_________________Begin - Part A_______________
   
   Serial.begin(115200);

   int x=0;
   for (x=0; x<8; x++){
    pinMode(led_pins[x], OUTPUT);
   }
   
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
     Serial.readBytes(((char*)&incoming),1);      
     Serial.println(incoming);
     dl = incoming >> 4;
     Serial.println(dl); 
     mlt = incoming % (1<<4);
     Serial.println(mlt); 
   }
   //_________________End - Part B_________________
   
   
   //_________________Begin - Part C_______________
   // loop over all output (LED) pins and set state to HIGH/LOW
   // e.g. digitalWrite(1,LOW) means you set the digital pin 1 to LOW.
   for (j =0;j<8;j++)
   {
     for (i=0;i<8;i++)
       digitalWrite(led_pins[i],LOW); // belongs to second for-loop
     digitalWrite(led_pins[j],HIGH);  // does not belong to second for-loop
     delay(dl*mlt);
   }   // First iteration [HIGH LOW LOW LOW LOW LOW LOW LOW] second iteration [01000000], third iteration [00100000] and so on, a lighting LED moves through the array. 
   delay(dl*mlt*3);
   //_________________End - Part C_________________
   


   //_________________Begin - Part D_______________

   /*
   delay(10);
   */
   //_________________End - Part D_________________
   
   }

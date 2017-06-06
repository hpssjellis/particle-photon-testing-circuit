// Photon Tester
// By Jeremy Ellis June 2017
// MIT license


int myTesting, myUsing;  
String myTestName;
bool digitalHighGood, digitalLowGood;
String myPinsGood[] = {"Bad", "Bad", "Bad", "Bad", "Bad", "Bad", "Bad", "Bad", "Bad", "Bad", 
                       "Bad", "Bad", "Bad", "Bad", "Bad", "Bad", 
                       "Bad", "Bad", "Bad", "Bad", "Bad"};  

String myPinsName[] = {"D0", "D1", "D2", "D3", "D4", "D5", "D6", "D7", "non8","non9",   // PINS  0 - 7
                       "A0", "A1", "A2", "A3", "A4", "A5",                // PINS 10 - 15
                       "DAC", "WKP", "RX", "TX", "BTN", "generic1", "generic2"};                  // PINS 16 - 20
                       
                       
                       
                       
//String myDAC1Good = "Bad"; 
//String myDAC2Good = "Bad";   

String myPWM_A4  = "Bad";
String myPWM_A5  = "Bad";
String myPWM_WKP = "Bad";
String myPWM_RX  = "Bad";
String myPWM_TX  = "Bad";
String myPWM_D0  = "Bad";
String myPWM_D1  = "Bad";
String myPWM_D2  = "Bad";
String myPWM_D3  = "Bad";
String myPWM_D4  = "Bad";




String myAnalogA0 = "Bad";
String myAnalogA1 = "Bad";
String myAnalogA2 = "Bad";
String myAnalogA3 = "Bad";
String myAnalogA4 = "Bad";
String myAnalogA5 = "Bad";
String myAnalogDAC1 = "Bad";
String myAnalogWKP = "Bad";


String Serial_uART  = "Bad";
String Serial_I2C   = "Bad";
String Serial_SPI   = "Bad";




//int myAReadPinNum[] = {A0, A1, A2, A3, A4, A5, A6, A7};
//int myPWMPinNum[]   = {A4, A5, WKP, RX, TX, D0, D1, D2, D3};  //D2,D3 only work if A4,A5 not used for PWM
//String myAReadPinGooD[] = {"Bad", "Bad", "Bad", "Bad", "Bad", "Bad", "Bad", "Bad"};
//String myPWMPinGood[]   = {"Bad", "Bad", "Bad", "Bad", "Bad", "Bad", "Bad", "Bad", "Bad"};  //D2,D3 only work if A4,A5 not used for PWM
                       
                    // D0  0
                    // D7  7
                    // note do not use 8,9
                    //  A0 = 10
                    //  A7 = 17
                    //  Rx = 18, TX=19
void setup() {





// Just my testing area

//pinMode(30,INPUT);
   // Particle.publish(String(Reset),"Reset button number", 60, PRIVATE);
   // delay(1000);
  // pinMode(8, OUTPUT);

   // for (int myPin=0; myPin <= 19; myPin++){
   //     if (myPin == 8){myPin = 10;}
      
   //     Particle.publish("Pin count = ",String(myPin), 60, PRIVATE);
   //     delay(1000);
 // }


}


void resetAllToInput(){
  
    for (int myPin=0; myPin <= 19; myPin++){ // reset all GPIO pins to inputs
        if (myPin == 8){myPin = 10;}   // to skip pins 8 and 9 
        pinMode(myPin, INPUT);
    }  
    
}



void myTestDigitalInOut(){
    // test all digital inputs by sending them 3.3V and outout the results to the console
    // schematic needs lines from 3.3 to every GPIO input
    // somehow these lines need to be activated. How is this done?
    // Output to console ??
    

    for (int myPin=0; myPin <= 19; myPin++){  // only to 18 as the last is connected special TX to D0 
        if (myPin == 8){myPin = 10;}   // to skip pins 8 and 9 

    myUsing  = myPin+1;   // the output pin
        if (myPin == D7){ myUsing = A0; }   // D7 connected to A0 7->10
        if (myPin == TX){ myUsing = D0; }   // D7 connected to A0 19->0
    myTesting  = myPin;    // the pin to test


    pinMode(myTesting, INPUT);
    pinMode(myUsing , OUTPUT);
    digitalWrite(myUsing , HIGH);
    if (digitalRead(myTesting) == HIGH){ digitalHighGood = true; } else { digitalHighGood = false; }
    digitalWrite(myUsing , LOW);
    if (digitalRead(myTesting) == LOW){  digitalLowGood= true; } else { digitalLowGood= false; }  
    if ( digitalHighGood &&  digitalLowGood){ myPinsGood[myTesting] = "Good"; } else { myPinsGood[myTesting]= "Bad"; }
    Particle.publish("digitalWrite("+myPinsName[myUsing]+")-digitalRead(" + myPinsName[myTesting] + ")", myPinsGood[myTesting], 60, PRIVATE);
    delay(1000);
    
    }
    
    //Then test the last pin TX
  

       

}












void myTestPWM(){  
    
    // not testing PWM on TX or RX since they mess it up
    
    unsigned long duration;
    bool lowGood, highGood;
    int mySetPWM;  // do not use 0 or 255
    pinMode(D6, INPUT_PULLDOWN);
    // each PWM pin connected to an unused DigitalRead pin sugggest D6 for all
    
    mySetPWM = random(1, 254); 
    pinMode(A4, OUTPUT);
    analogWrite(A4, mySetPWM);
    duration = pulseIn(D6, HIGH);
    if (duration > mySetPWM * 7.84 * 0.9 && duration < mySetPWM * 7.84 * 1.1 ){ myPWM_A4 = "Good";} else {myPWM_A4 = "Bad";}
    Particle.publish("PWM A4, "+String(mySetPWM)+" = "+String(mySetPWM * 7.84, 0),String(duration)+" (ms)" , 60, PRIVATE);
    delay(1000);
    Particle.publish("PWM A4 is", myPWM_A4, 60, PRIVATE);
    delay(1000);    
    pinMode(A4, INPUT);  // reset pin    
    duration = pulseIn(D6, LOW);
    
    mySetPWM = random(1, 254);     
    pinMode(A5, OUTPUT);
    analogWrite(A5, mySetPWM);
    duration = pulseIn(D6, HIGH);
    if (duration > mySetPWM * 7.84 * 0.9 && duration < mySetPWM * 7.84 * 1.1 ){ myPWM_A5 = "Good";} else {myPWM_A5 = "Bad";}
    Particle.publish("PWM A5, "+String(mySetPWM)+" = "+String(mySetPWM * 7.84, 0),String(duration)+" (ms)" , 60, PRIVATE);
    delay(1000);
    Particle.publish("PWM A5 is", myPWM_A5, 60, PRIVATE);
    delay(1000);  
    pinMode(A5, INPUT);  // reset pin    
    duration = pulseIn(D6, LOW);      
        
    mySetPWM = random(1, 254);     
    pinMode(WKP, OUTPUT);
    analogWrite(WKP, mySetPWM);
    duration = pulseIn(D6, HIGH);
    if (duration > mySetPWM * 7.84 * 0.9 && duration < mySetPWM * 7.84 * 1.1 ){ myPWM_WKP = "Good";} else {myPWM_WKP = "Bad";}
    Particle.publish("PWM WKP, "+String(mySetPWM)+" = "+String(mySetPWM * 7.84, 0),String(duration)+" (ms)" , 60, PRIVATE);
    delay(1000);
    Particle.publish("PWM WKP (A6) is", myPWM_WKP, 60, PRIVATE);
    delay(1000);   
    pinMode(WKP, INPUT);  // reset pin    
    duration = pulseIn(D6, LOW);      
     
    mySetPWM = random(1, 254);     
    pinMode(TX, OUTPUT);
    analogWrite(TX, mySetPWM);
    duration = pulseIn(D6, HIGH);
    if (duration > mySetPWM * 7.84 * 0.9 && duration < mySetPWM * 7.84 * 1.1 ){ myPWM_TX = "Good";} else {myPWM_TX = "Bad";}
    Particle.publish("PWM TX, "+String(mySetPWM)+" = "+String(mySetPWM * 7.84, 0),String(duration)+" (ms)" , 60, PRIVATE);
    delay(1000);
    Particle.publish("PWM TX is", myPWM_A5, 60, PRIVATE);
    delay(1000);  
    pinMode(TX, INPUT);  // reset pin    
    duration = pulseIn(D6, LOW);      
            
    mySetPWM = random(1, 254);     
    pinMode(RX, OUTPUT);
    analogWrite(RX, mySetPWM);
    duration = pulseIn(D6, HIGH);
    if (duration > mySetPWM * 7.84 * 0.9 && duration < mySetPWM * 7.84 * 1.1 ){ myPWM_RX = "Good";} else {myPWM_RX = "Bad";}
    Particle.publish("PWM RX, "+String(mySetPWM)+" = "+String(mySetPWM * 7.84, 0),String(duration)+" (ms)" , 60, PRIVATE);
    delay(1000);
    Particle.publish("PWM RX is", myPWM_A5, 60, PRIVATE);
    delay(1000);  
    pinMode(RX, INPUT);  // reset pin    
    duration = pulseIn(D6, LOW);      
               
    mySetPWM = random(1, 254); 
    pinMode(D0, OUTPUT);
    analogWrite(D0, mySetPWM);
    duration = pulseIn(D6, HIGH);
    if (duration > mySetPWM * 7.84 * 0.9 && duration < mySetPWM * 7.84 * 1.1 ){ myPWM_D0 = "Good";} else {myPWM_D0 = "Bad";}
    Particle.publish("PWM D0, "+String(mySetPWM)+" = "+String(mySetPWM * 7.84, 0),String(duration)+" (ms)" , 60, PRIVATE);
    delay(1000);
    Particle.publish("PWM D0 is", myPWM_D0, 60, PRIVATE);
    delay(1000);    
    pinMode(D0, INPUT);  // reset pin    
    duration = pulseIn(D6, LOW);

    mySetPWM = random(1, 254); 
    pinMode(D1, OUTPUT);
    analogWrite(D1, mySetPWM);
    duration = pulseIn(D6, HIGH);
    if (duration > mySetPWM * 7.84 * 0.9 && duration < mySetPWM * 7.84 * 1.1 ){ myPWM_D1 = "Good";} else {myPWM_D1 = "Bad";}
    Particle.publish("PWM D1, "+String(mySetPWM)+" = "+String(mySetPWM * 7.84, 0),String(duration)+" (ms)" , 60, PRIVATE);
    delay(1000);
    Particle.publish("PWM D1 is", myPWM_D1, 60, PRIVATE);
    delay(1000);    
    pinMode(D1, INPUT);  // reset pin    
    duration = pulseIn(D6, LOW);
    
    mySetPWM = random(1, 254); 
    pinMode(D2, OUTPUT);
    analogWrite(D2, mySetPWM);
    duration = pulseIn(D6, HIGH);
    if (duration > mySetPWM * 7.84 * 0.9 && duration < mySetPWM * 7.84 * 1.1 ){ myPWM_D2 = "Good";} else {myPWM_D2 = "Bad";}
    Particle.publish("PWM D2, "+String(mySetPWM)+" = "+String(mySetPWM * 7.84, 0),String(duration)+" (ms)" , 60, PRIVATE);
    delay(1000);
    Particle.publish("PWM D2 is", myPWM_D2, 60, PRIVATE);
    delay(1000);    
    pinMode(D2, INPUT);  // reset pin    
    duration = pulseIn(D6, LOW);
    
    mySetPWM = random(1, 254); 
    pinMode(D3, OUTPUT);
    analogWrite(D3, mySetPWM);
    duration = pulseIn(D6, HIGH);
    if (duration > mySetPWM * 7.84 * 0.9 && duration < mySetPWM * 7.84 * 1.1 ){ myPWM_D3 = "Good";} else {myPWM_D3 = "Bad";}
    Particle.publish("PWM D3, "+String(mySetPWM)+" = "+String(mySetPWM * 7.84, 0),String(duration)+" (ms)" , 60, PRIVATE);
    delay(1000);
    Particle.publish("PWM D3 is", myPWM_D3, 60, PRIVATE);
    delay(1000);    
    pinMode(D3, INPUT);  // reset pin    
    duration = pulseIn(D6, LOW);
    

}










void myTestAnalogUsingDac(){
    
    // String myDAC1Good = "Bad";  //decalred as a global variable
    // String myDAC2Good = "Bad";  // declared as a global variable    
    
    int myDacRead1000, myDacRead2000, myDacRead3000;
    String myDac1Output,myDac2Output ;
    
    
    
    
    
    pinMode(DAC1, OUTPUT);    // DAC1 = A6 for output
    analogWrite(DAC1, 1000);    
    myDacRead1000 = analogRead(A0);
    analogWrite(DAC1, 2000);    
    myDacRead2000 = analogRead(A0);
    analogWrite(DAC1, 3000);    
    myDacRead3000 = analogRead(A0);
    
    myDac1Output = String(myDacRead1000) + ", "+String(myDacRead2000) + ", "+ String(myDacRead3000) ;
    if (myDacRead1000 > 900 && myDacRead1000 < 1100 && myDacRead2000 > 1900 && myDacRead2000 < 2100 && myDacRead3000 > 2900 && myDacRead3000 < 3100){
        myAnalogA0 = "Good";
    } else {myAnalogA0 = "Bad";}
  
    Particle.publish("AnalogWrite DAC1 AnalogRead A0", myDac1Output , 60, PRIVATE);
    delay(1000);
    Particle.publish("AnalogWrite DAC1 AnalogRead A0", myAnalogA0 , 60, PRIVATE);
    delay(1000);     
    
    
     
    
    pinMode(DAC1, OUTPUT);    // DAC1 = A6 for output
    analogWrite(DAC1, 1000);    
    myDacRead1000 = analogRead(A1);
    analogWrite(DAC1, 2000);    
    myDacRead2000 = analogRead(A1);
    analogWrite(DAC1, 3000);    
    myDacRead3000 = analogRead(A1);
    
    myDac1Output = String(myDacRead1000) + ", "+String(myDacRead2000) + ", "+ String(myDacRead3000) ;
    if (myDacRead1000 > 900 && myDacRead1000 < 1100 && myDacRead2000 > 1900 && myDacRead2000 < 2100 && myDacRead3000 > 2900 && myDacRead3000 < 3100){
        myAnalogA1 = "Good";
    } else {myAnalogA1 = "Bad";}
  
    Particle.publish("AnalogWrite DAC1 AnalogRead A1", myDac1Output , 60, PRIVATE);
    delay(1000);
    Particle.publish("AnalogWrite DAC1 AnalogRead A1", myAnalogA1 , 60, PRIVATE);
    delay(1000);     
    
    
    
    
    
    pinMode(DAC1, OUTPUT);    // DAC1 = A6 for output
    analogWrite(DAC1, 1000);    
    myDacRead1000 = analogRead(A2);
    analogWrite(DAC1, 2000);    
    myDacRead2000 = analogRead(A2);
    analogWrite(DAC1, 3000);    
    myDacRead3000 = analogRead(A2);
    
    myDac1Output = String(myDacRead1000) + ", "+String(myDacRead2000) + ", "+ String(myDacRead3000) ;
    if (myDacRead1000 > 900 && myDacRead1000 < 1100 && myDacRead2000 > 1900 && myDacRead2000 < 2100 && myDacRead3000 > 2900 && myDacRead3000 < 3100){
        myAnalogA2 = "Good";
    } else {myAnalogA2 = "Bad";}
  
    Particle.publish("AnalogWrite DAC1 AnalogRead A2", myDac1Output , 60, PRIVATE);
    delay(1000);
    Particle.publish("AnalogWrite DAC1 AnalogRead A2", myAnalogA2 , 60, PRIVATE);
    delay(1000);     
    
    
        
    
    pinMode(DAC1, OUTPUT);    // DAC1 = A6 for output
    analogWrite(DAC1, 1000);    
    myDacRead1000 = analogRead(A3);
    analogWrite(DAC1, 2000);    
    myDacRead2000 = analogRead(A3);
    analogWrite(DAC1, 3000);    
    myDacRead3000 = analogRead(A3);
    
    myDac1Output = String(myDacRead1000) + ", "+String(myDacRead2000) + ", "+ String(myDacRead3000) ;
    if (myDacRead1000 > 900 && myDacRead1000 < 1100 && myDacRead2000 > 1900 && myDacRead2000 < 2100 && myDacRead3000 > 2900 && myDacRead3000 < 3100){
        myAnalogA3 = "Good";
    } else {myAnalogA3 = "Bad";}
  
    Particle.publish("AnalogWrite DAC1 AnalogRead A3", myDac1Output , 60, PRIVATE);
    delay(1000);
    Particle.publish("AnalogWrite DAC1 AnalogRead A3", myAnalogA3 , 60, PRIVATE);
    delay(1000);     
    
    
    

       
    
    pinMode(DAC1, OUTPUT);    // DAC1 = A6 for output
    analogWrite(DAC1, 1000);    
    myDacRead1000 = analogRead(A4);
    analogWrite(DAC1, 2000);    
    myDacRead2000 = analogRead(A4);
    analogWrite(DAC1, 3000);    
    myDacRead3000 = analogRead(A4);
    
    myDac1Output = String(myDacRead1000) + ", "+String(myDacRead2000) + ", "+ String(myDacRead3000) ;
    if (myDacRead1000 > 900 && myDacRead1000 < 1100 && myDacRead2000 > 1900 && myDacRead2000 < 2100 && myDacRead3000 > 2900 && myDacRead3000 < 3100){
        myAnalogA4 = "Good";
    } else {myAnalogA4 = "Bad";}
  
    Particle.publish("AnalogWrite DAC1 AnalogRead A4", myDac1Output , 60, PRIVATE);
    delay(1000);
    Particle.publish("AnalogWrite DAC1 AnalogRead A4", myAnalogA4 , 60, PRIVATE);
    delay(1000);     
    
    
      
    
    
    
    
    

      
    
    pinMode(DAC2, OUTPUT);    // DAC2 = A3 for output
    analogWrite(DAC2, 1000);    
    myDacRead1000 = analogRead(A5);
    analogWrite(DAC2, 2000);    
    myDacRead2000 = analogRead(A5);
    analogWrite(DAC2, 3000);    
    myDacRead3000 = analogRead(A5);
    
    myDac2Output = String(myDacRead1000) + ", "+String(myDacRead2000) + ", "+ String(myDacRead3000) ;
    if (myDacRead1000 > 900 && myDacRead1000 < 1100 && myDacRead2000 > 1900 && myDacRead2000 < 2100 && myDacRead3000 > 2900 && myDacRead3000 < 3100){
        myAnalogA5 = "Good";
    } else {myAnalogA5 = "Bad";}
   
    Particle.publish("AnalogWrite DAC2 AnalogRead A5", myDac2Output , 60, PRIVATE);
    delay(1000);
    Particle.publish("AnalogWrite DAC2 AnalogRead A5", myAnalogA5 , 60, PRIVATE);
    delay(1000);
    
    
        
    
    pinMode(DAC2, OUTPUT);    // DAC2 = A3 for output
    analogWrite(DAC2, 1000);    
    myDacRead1000 = analogRead(DAC1);
    analogWrite(DAC2, 2000);    
    myDacRead2000 = analogRead(DAC1);
    analogWrite(DAC2, 3000);    
    myDacRead3000 = analogRead(DAC1);
    
    myDac2Output = String(myDacRead1000) + ", "+String(myDacRead2000) + ", "+ String(myDacRead3000) ;
    if (myDacRead1000 > 900 && myDacRead1000 < 1100 && myDacRead2000 > 1900 && myDacRead2000 < 2100 && myDacRead3000 > 2900 && myDacRead3000 < 3100){
        myAnalogDAC1 = "Good";
    } else {myAnalogDAC1 = "Bad";}
   
    Particle.publish("AnalogWrite DAC2 AnalogRead DAC1", myDac2Output , 60, PRIVATE);
    delay(1000);
    Particle.publish("AnalogWrite DAC2 AnalogRead DAC1", myAnalogDAC1 , 60, PRIVATE);
    delay(1000);
    
    
        
    
    pinMode(DAC2, OUTPUT);    // DAC2 = A3 for output
    analogWrite(DAC2, 1000);    
    myDacRead1000 = analogRead(WKP);
    analogWrite(DAC2, 2000);    
    myDacRead2000 = analogRead(WKP);
    analogWrite(DAC2, 3000);    
    myDacRead3000 = analogRead(WKP);
    
    myDac2Output = String(myDacRead1000) + ", "+String(myDacRead2000) + ", "+ String(myDacRead3000) ;
    if (myDacRead1000 > 900 && myDacRead1000 < 1100 && myDacRead2000 > 1900 && myDacRead2000 < 2100 && myDacRead3000 > 2900 && myDacRead3000 < 3100){
        myAnalogWKP = "Good";
    } else {myAnalogWKP = "Bad";}
   
    Particle.publish("AnalogWrite DAC2 AnalogRead WKP", myDac2Output , 60, PRIVATE);
    delay(1000);
    Particle.publish("AnalogWrite DAC2 AnalogRead WKP", myAnalogWKP , 60, PRIVATE);
    delay(1000);
    
    
      
    
    
    
    
    
    
    
    
    // test both DAC lines
    // schematic needs lines from DAC1 (A6) to A1;
    // schematic needs lines from DAC2 (A3) to A2;
    // somehow these lines need to be activated. How is this done?
    // Output to console ??    
}






void loop() {


    resetAllToInput();
    
    //myTestDigitalInOut();   //bracket out since working
    //resetAllToInput();
    
  //  myTestAnalogInOut();   // A4 and A5 Not accurate or efficient
  //  resetAllToInput();
  
    // myTestPWM();   // working must test TX and RX without serial1 active
    //resetAllToInput();
  
    
    myTestAnalogUsingDac();   
    resetAllToInput();
    

    
    Particle.publish("---", "---", 60, PRIVATE);
    delay(3000);

}

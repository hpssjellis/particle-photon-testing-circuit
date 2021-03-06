// Photon Tester
// By Jeremy Ellis June 2017
// MIT license

// Make sure you flash the code before connecting your Photon
// ALL GPIO pins are conencted together !!  (TX --> A0 and D7 --> D0 and bridge the two groups.)
// Do not connect any of the other PINS!




int myTesting, myUsing;  
String myTestName;
bool digitalHighGood, digitalLowGood;
String myPinsGood[] = {"Bad", "Bad", "Bad", "Bad", "Bad", "Bad", "Bad", "Bad", "Bad", "Bad", 
                       "Bad", "Bad", "Bad", "Bad", "Bad", "Bad", 
                       "Bad", "Bad", "Bad", "Bad", "Bad"};  

String myPinsName[] = {"D0", "D1", "D2", "D3", "D4", "D5", "D6", "D7", "non8","non9",   // PINS  0 - 7
                       "A0", "A1", "A2", "A3", "A4", "A5",                // PINS 10 - 15
                       "DAC", "WKP", "RX", "TX", "BTN", "generic1", "generic2"};                  // PINS 16 - 20
                       
                       
String myDAC1Good[] = {"Bad", "Bad", "Bad", "Bad", "Bad", "Bad", "Bad"}; 
String    myDac1Names[] = {"A0", "A1", "A2", "A3", "A4", "A5", "WKP"};
int    myDac1Pins[] = {A0, A1, A2, A3, A4, A5, WKP};


String myDAC2Good[] = {"Bad", "Bad", "Bad", "Bad", "Bad", "Bad", "Bad"}; 
String    myDac2Names[] = {"A0", "A1", "A2", "A4", "A5", "DAC1", "WKP"};
int    myDac2Pins[] = {A0, A1, A2, A4, A5, DAC1, WKP};

 

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



void setup() {

}


void resetAllToInput(){
  
    for (int myPin=0; myPin <= 19; myPin++){ // reset all GPIO pins to inputs
        if (myPin == 8){myPin = 10;}   // to skip pins 8 and 9 
        pinMode(myPin, INPUT);
    }  
    
}



void myTestDigitalInOut(){

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
    

}


void myTestPWM(){  
    
    
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
    

    
    int myDacRead1000, myDacRead2000, myDacRead3000;
    String myDacOutput ;
    
   // checks all analog reads except DAC1 (A6) using DAC1 
    
    for (int myPin = 0; myPin <= 6; myPin++){
    
        pinMode(DAC1, OUTPUT);    // DAC1 = A6 for output
        analogWrite(DAC1, 1000);    
        myDacRead1000 = analogRead( myDac1Pins[myPin] );
        analogWrite(DAC1, 2000);    
        myDacRead2000 = analogRead(myDac1Pins[myPin]);
        analogWrite(DAC1, 3000);    
        myDacRead3000 = analogRead(myDac1Pins[myPin]);
        digitalWrite(DAC1, LOW);
        pinMode(DAC1, INPUT);
        
        
        myDacOutput = String(myDacRead1000) + ", "+String(myDacRead2000) + ", "+ String(myDacRead3000) ;
        if (myDacRead1000 > 900 && myDacRead1000 < 1100 && myDacRead2000 > 1900 && myDacRead2000 < 2100 && myDacRead3000 > 2900 && myDacRead3000 < 3100){
            myDAC1Good[myPin] = "Good";
        } else {myDAC1Good[myPin] = "Bad";}
      
        Particle.publish("Write DAC1, Read " + String(myDac1Names[myPin]), myDacOutput , 60, PRIVATE);
        delay(2000);
        Particle.publish("Write DAC1, Read " + String(myDac1Names[myPin]), myDAC1Good[myPin] , 60, PRIVATE);
        delay(2000);     
        pinMode( myDac1Pins[myPin] , INPUT);  // reset pin      

    }





   // checks all analog reads except DAC2 (A3) using DAC2 
    
    for (int myPin = 0; myPin <= 6; myPin++){
       
        pinMode(DAC2, OUTPUT);    // DAC1 = A6 for output
        analogWrite(DAC2, 1000);    
        myDacRead1000 = analogRead( myDac2Pins[myPin] );
        analogWrite(DAC2, 2000);    
        myDacRead2000 = analogRead(myDac2Pins[myPin]);
        analogWrite(DAC2, 3000);    
        myDacRead3000 = analogRead(myDac2Pins[myPin]);
        digitalWrite(DAC2, LOW);
        pinMode(DAC2, INPUT);
        
        myDacOutput = String(myDacRead1000) + ", "+String(myDacRead2000) + ", "+ String(myDacRead3000) ;
        if (myDacRead1000 > 900 && myDacRead1000 < 1100 && myDacRead2000 > 1900 && myDacRead2000 < 2100 && myDacRead3000 > 2900 && myDacRead3000 < 3100){
            myDAC2Good[myPin] = "Good";
        } else {myDAC2Good[myPin] = "Bad";}
      
        Particle.publish("Write DAC2, Read " + String(myDac2Names[myPin]), myDacOutput , 60, PRIVATE);
        delay(2000);
        Particle.publish("Write DAC2, Read " + String(myDac2Names[myPin]), myDAC2Good[myPin] , 60, PRIVATE);
        delay(2000);     
        pinMode( myDac2Pins[myPin] , INPUT);  // reset pin      

    }

}

void loop() {   // main loop

    resetAllToInput();
    
    
    myTestDigitalInOut();   
    resetAllToInput();
    
    
    myTestPWM();   
    resetAllToInput();
  
    
    myTestAnalogUsingDac();   
    resetAllToInput();
    
    
    Particle.publish("Analyse the results", "waiting 30 (s) to repeat", 60, PRIVATE);
    delay(30000);   //wait 30 s

}

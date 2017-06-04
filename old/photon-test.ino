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
                       
                       
                       
                       
String myDAC1Good = "Bad"; 
String myDAC2Good = "Bad";   

//int myAReadPinNum[] = {A0, A1, A2, A3, A4, A5, A6, A7};
//int myPWMPinNum[]   = {A4, A5, PWK, RX, TX, D0, D1, D2, D3};  //D2,D3 only work if A4,A5 not used for PWM
//String myAReadPinGooD[] = {"Bad", "Bad", "Bad", "Bad", "Bad", "Bad", "Bad", "Bad"};
//String myPWMPinGood[]   = {"Bad", "Bad", "Bad", "Bad", "Bad", "Bad", "Bad", "Bad", "Bad"};  //D2,D3 only work if A4,A5 not used for PWM
                       
                       // D0  0
                    // D7  7
                    // note no use 8,9
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





void myTestAnalogInOut(){
    

    // test all analog outputs (PWM specific PINS A4, A5, TX, RX, D0, D1, D2?, D3?, DAC1,2 ?) LED will vary in brightness
    // schematic needs lines from each GPIO to a resistor and LED and then GND
    // somehow these lines need to be activated. How is this done?
    // Output to console ?? 
    
    
    
    
    
}





void myTestDAC(){
    
    // String myDAC1Good = "Bad";  //decalred as a global variable
    // String myDAC2Good = "Bad";  // declared as a global variable    
    
    int myDacRead1000, myDacRead2000, myDacRead3000;
    String myDac1Output,myDac2Output ;
    
    
    pinMode(DAC1, OUTPUT);    // DAC1 = A6 for output
    analogWrite(DAC1, 1000);    
    myDacRead1000 = analogRead(A1);
    analogWrite(DAC1, 2000);    
    myDacRead2000 = analogRead(A1);
    analogWrite(DAC1, 3000);    
    myDacRead3000 = analogRead(A1);
    
    myDac1Output = String(myDacRead1000) + ", "+String(myDacRead2000) + ", "+ String(myDacRead3000) ;
    if (myDacRead1000 > 900 && myDacRead1000 < 1100 && myDacRead2000 > 1900 && myDacRead2000 < 2100 && myDacRead3000 > 2900 && myDacRead3000 < 3100){
        myDAC1Good = "Good";
    }
  
    Particle.publish("AnalogWrite DAC1 AnalogRead A1", myDac1Output , 60, PRIVATE);
    delay(1000);
    Particle.publish("AnalogWrite DAC1 AnalogRead A1", myDAC1Good , 60, PRIVATE);
    delay(1000);     
    
    pinMode(DAC2, OUTPUT);    // DAC1 = A6 for output
    analogWrite(DAC2, 1000);    
    myDacRead1000 = analogRead(A2);
    analogWrite(DAC2, 2000);    
    myDacRead2000 = analogRead(A2);
    analogWrite(DAC2, 3000);    
    myDacRead3000 = analogRead(A2);
    
    myDac2Output = String(myDacRead1000) + ", "+String(myDacRead2000) + ", "+ String(myDacRead3000) ;
    if (myDacRead1000 > 900 && myDacRead1000 < 1100 && myDacRead2000 > 1900 && myDacRead2000 < 2100 && myDacRead3000 > 2900 && myDacRead3000 < 3100){
        myDAC2Good = "Good";
    }
   
    Particle.publish("AnalogWrite DAC2 AnalogRead A2", myDac2Output , 60, PRIVATE);
    delay(1000);
    Particle.publish("AnalogWrite DAC2 AnalogRead A2", myDAC2Good , 60, PRIVATE);
    delay(1000);
    // test both DAC lines
    // schematic needs lines from DAC1 (A6) to A1;
    // schematic needs lines from DAC2 (A3) to A2;
    // somehow these lines need to be activated. How is this done?
    // Output to console ??    
}


void myUART(){
    // connect second photon and run program using console
    // Schematic needs lines from TX, TR the other for each photon
}


void myI2C(){
    // connect second photon and run program using console
    // Schematic needs lines from D0, D1
}



void mySPI(){
    // connect second photon and run program using console
    // Schematic needs lines from A2, A3, A4, A5 to each photon
}




void loop() {


    resetAllToInput();
    
    myTestDigitalInOut();
    resetAllToInput();
    
    myTestAnalogInOut();
    resetAllToInput();
    
    myTestDAC();
    resetAllToInput();
    
    myUART();
    resetAllToInput();
    
    myI2C();
    resetAllToInput();
    
    mySPI();
    resetAllToInput();
    
    Particle.publish("---", "---", 60, PRIVATE);
    delay(3000);

}

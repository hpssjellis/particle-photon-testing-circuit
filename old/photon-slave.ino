// Photon Tester
// By Jeremy Ellis June 2017
// MIT license





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




void myUART(){
    // connect second photon and run program using console
    // Schematic needs lines from TX, TR the other for each photon
    
    // Master working photon 
    // Slave unknown photon
    // connect GND to GND
    // on Master TX to slave RX
    // On Master RX to slave TX
    
    
    // following declared in setup
   // Serial.begin(9600);  // only if using this photon as a slave?
   
    Serial1.begin(9600);  // only if using this photon as a slave?
    
    Particle.publish("uART Serial1 started", "On TX and RX", 60, PRIVATE);

    if (Serial1.available() > 0) {
        
        Particle.publish("Serial1 Available", "---", 60, PRIVATE);
        delay(1000);
        int incomingFromMaster = Serial1.read();
        if (incomingFromMaster == 'A') {
            Serial_uART = "Good";
            Particle.publish("Serial1 working A = 65", String(incomingFromMaster), 60, PRIVATE);
            Serial1.write('B');
            delay(1000);            
            
       } else {Serial_uART = "Bad";}
       
    }
    Particle.publish("uART Serial is", Serial_uART, 60, PRIVATE);
    delay(1000); 
    
    Serial1.end();  // only if using this photon as a slave?
    
    Particle.publish("uART serial1 disconnecting", "Test finished", 60, PRIVATE);
    delay(1000);
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
    

    myUART();   // move to photon slave.ino 
    resetAllToInput();
    
    myI2C();
    resetAllToInput();
    
    mySPI();
    resetAllToInput();
    
    Particle.publish("---", "---", 60, PRIVATE);
    delay(3000);

}

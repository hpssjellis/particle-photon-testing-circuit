// Photon Tester
// By Jeremy Ellis June 2017
// MIT license


int x = 2;


String Serial_uART  = "Bad";
String Serial_I2C   = "Bad";
String Serial_SPI   = "Bad";




void setup() {

    // Master working photon 
    // Slave unknown photon
    // connect GND to GND
    // on Master TX to slave RX
    // On Master RX to slave TX
    
    
    // following declared in setup

   
//    Serial1.begin(9600);  // only if using this photon as a slave?
    
//    Particle.publish("uART Serial1 started", "On TX and RX", 60, PRIVATE);
//    delay(1000);
    
    
    Wire.begin(4);   // label this slave as # 9
    Wire.onReceive(receiveEvent);
    
    
    // Attach a function to trigger when something is received.
   // Wire.onRequest(requestEvent);
  //  Particle.publish("I2C Wire started", "On D0 (SDA) and D1 (SCL)", 60, PRIVATE);
   // delay(1000);
    

    

}


void receiveEvent(int bytes){
    x = (int)Wire.read();    // read one character from the I2C
    
   // Particle.publish("I2C activated", String(x), 60, PRIVATE);
    //Particle.publish("I2C sent from master", String(x), 60, PRIVATE);
    //delay(1000);

}


/*


void requestEvent() {
    Wire.write('C');         // respond with message of 6 bytes as expected by master
  
    Particle.publish("I2C sent to master a", String('C'), 60, PRIVATE);
    delay(1000);
}



*/


void myUART(){
    // connect second photon and run program using console
    // Schematic needs lines from TX, TR the other for each photon
    


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
    
   // Serial1.end();  // only if using this photon as a slave?
}    



void myI2C(){
    // connect second photon and run program using console
    // Schematic needs lines from D0, D1
    
   //If value received is 0 blink LED for 200 ms
    if (x == 0) {
        Particle.publish("I2C working", "sent a 0", 60, PRIVATE);
    }
  //If value received is 3 blink LED for 400 ms
    if (x == 3) {
        Particle.publish("I2C working", "sent a 3", 60, PRIVATE);
    }   
    
   delay(1000); 
    
}



void mySPI(){
    // connect second photon and run program using console
    // Schematic needs lines from A2, A3, A4, A5 to each photon
}




void loop() {

  //  myUART();   // move to photon slave.ino 

    myI2C();

 //   mySPI();

    
    Particle.publish("---", "---", 60, PRIVATE);
    delay(3000);

}

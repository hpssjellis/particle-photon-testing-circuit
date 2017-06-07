// Photon Tester Working Msater Photon
// By Jeremy Ellis June 2017
// MIT license


int x = 4;

    
    // Master working photon 
    // Slave unknown photon
    // connect GND to GND
    // on Master TX to slave RX
    // On Master RX to slave TX
    


    // Photon I2C setup
    // GND master to GND slave
    // D0 (SDA = data) on master to D0 on slave
    // D1 (SCL = clock) on Master to D1 on slave

void setup() {
   // Serial1.begin(9600);  // uART start TX, RX
    Wire.begin();         // I2C start DO, D1 

}

void myUart() {
  
      
    if (Serial1.available() > 0) {
        Serial1.write('A');
        Particle.publish("uART Serial working", "Sent an A", 60, PRIVATE);
        delay(1000);
        delay(1000);
    }
        if (Serial1.available() > 0) {
        int incomingFromSlave = Serial1.read();
        if (incomingFromSlave == 'B') {  
            Particle.publish("uART Serial working B = 66", String(incomingFromSlave), 60, PRIVATE);
            delay(1000);
        }  else {
             Particle.publish("Serial working", "No returned value", 60, PRIVATE);
             delay(1000);
        }
    } else  {
            Particle.publish("Serial Not working", "---", 60, PRIVATE);
            delay(1000);
        }
    delay(1000);
    
}



void myI2C(){
    
    Wire.beginTransmission(4); // transmit to device #9
    Wire.write(x);              // sends x 
    Wire.endTransmission();    // stop transmitting
    x++; // Increment x
    if (x > 5) x = 0; // reset x once it gets 6
    Particle.publish("I2C sent", String(x), 60, PRIVATE);
    delay(1000);  
    
  
  
  /*  
    Wire.requestFrom(9, 1);    // request 6 bytes from slave device #2

    while(Wire.available()){   // slave may send less than requested
        char c = Wire.read();    // receive a byte as character

         Particle.publish("I2C sent from slave", String(c), 60, PRIVATE);
         delay(1000);
    }
    
    */
    
}



void mySPI(){
    
    
    
}


void loop(){
//    myUart();
    myI2C();
 //   mySPI();
 delay(3000);
    
    
}

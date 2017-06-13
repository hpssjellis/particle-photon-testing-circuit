// Photon Tester Working Msater Photon
// By Jeremy Ellis June 2017
// MIT license
// Use at your own risk!

// Photon I2C setup
// GND master to GND slave
// D0 (SDA = data) on master to D0 on slave
// D1 (SCL = clock) on Master to D1 on slave
// pullup 4.7 K ohm resistor from D0 to 3V3
// pullup 4.7 K ohm resistor from D1 to 3V3


int idx;

String myI2cMasterIn; // Note: 32 chars Max string read 
String myI2cSlaveOut = "I2C slave out"; // Note: 32 chars Max string read 

void receiveEvent(int numOfBytes) {
    idx = 0;
    myI2cMasterIn = "";
    while (Wire.available()) { 
        myI2cMasterIn += "H";   // setCharAt needs a character to be able to replace it!
        myI2cMasterIn.setCharAt(idx, (char)Wire.read() );  
        idx ++;
    } 
}


void requestEvent() {
  Wire.write(myI2cSlaveOut);         // respond with message of 6 bytes as expected by master
}



void setup() {
   // Serial.begin(9600);
    Wire.begin(8);
    Wire.onReceive(receiveEvent);   // so slave can receive data
    Wire.onRequest(requestEvent);   // so slave can send data


}

void loop() {            
   // Particle.publish("I2C received",String(idx),60,PRIVATE);
   // delay(10000);
   // if (idx != 0) {
        Particle.publish("I2C slave sent = " + myI2cSlaveOut,"I2C received from Master = " + myI2cMasterIn    ,60,PRIVATE);
        delay(5000);
       // idx = 0;
   // }
    
}

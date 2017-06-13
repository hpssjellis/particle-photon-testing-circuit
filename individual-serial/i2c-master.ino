
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


String myI2CSlaveIn; // Note: 32 chars Max string read 
String myI2CMasterOut = "I2C from Master"; 

void setup() {
    Wire.begin();     // without a number defines this as the master!

}



void loop() {      
    
    
    Wire.beginTransmission(8); // transmit to device #8   can be up to 128 devices?
    Wire.write(myI2CMasterOut);  // only sends 32 characters but you can try more
    Wire.endTransmission();

    Particle.publish("I2C Master sent", myI2CMasterOut, 60, PRIVATE);
    delay(1000);  
    
    

    Wire.requestFrom(8, 32);    // from slave #8 request MAX 32 reduce it if you know how many
  
    myI2CSlaveIn = "";
    idx = 0;
    while (Wire.available()) { 
       myI2CSlaveIn +="H";    // setCharAt needs a character to be able to replace it!
        myI2CSlaveIn.setCharAt(idx, (char)Wire.read() );  
        idx ++;
    }  

    
    Particle.publish("I2C Master sent =" + myI2CMasterOut,"I2C received from Slave = " + myI2CSlaveIn , 60, PRIVATE);
    delay(5000);


}

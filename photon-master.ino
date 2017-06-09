// Photon Tester Working Msater Photon
// By Jeremy Ellis June 2017
// MIT license


int x = 4;
String myMasterOut, myMasterIn;

    
    // Master working photon 
    // Slave unknown photon
    // connect GND to GND
    // on Master TX to slave RX
    // On Master RX to slave TX
    


    // Photon I2C setup
    // GND master to GND slave
    // D0 (SDA = data) on master to D0 on slave
    // D1 (SCL = clock) on Master to D1 on slave
    // pullup 470 k ohm resistor from D0 to 3V3
    // pullup 470 k ohm resistor from D1 to 3V3

void setup() {
    Serial1.begin(9600);  // uART start TX, RX
    Wire.begin();         // I2C start DO, D1 

}

String incomingFromSlave;


void myUart() {
  
      
    if (Serial1.available() > 0) {
        Serial1.write("Fred");
        Particle.publish("uART Serial working", "Sent an A", 60, PRIVATE);
       // delay(1000);


    
    int idu = 0;
    incomingFromSlave = "";


     while(Serial1.available()){   
       // Particle.publish("Serial1 Available", "---", 60, PRIVATE);
       // delay(1000);
        //int incomingFromMaster = Serial1.read();
        incomingFromSlave += 'H';   // for setCharAt to work the string needs a character to replace
        incomingFromSlave.setCharAt(idu, (char)Serial1.read() );    // update string
        idu ++;
     }  
    }   
        
        
        if (incomingFromSlave == "TOM") {  
            Particle.publish("uART Serial working ", String(incomingFromSlave), 60, PRIVATE);
            delay(1000);
        }  else {
             Particle.publish("Serial working", "No returned value", 60, PRIVATE);
             delay(1000);
        }
  
    
}




void myI2C(){
    
    Wire.beginTransmission(8); // transmit to device #9
    
    // only sends 32 characters but you can try more
    // myMasterOut= "12345678901234567890123456789012";  // max length
    myMasterOut= "I2C from Master";  // max length
    Wire.write(myMasterOut);
    Wire.endTransmission();

    Particle.publish("I2C Master sent", myMasterOut, 60, PRIVATE);
    delay(1000);  

    Wire.requestFrom(8, 14);    // from slave #8 request MAX 32 or fewer bytes
    
    int idx = 0;
    myMasterIn = "";
    while(Wire.available()){   // slave may send less than requested
        myMasterIn += 'H';   // for setCharAt to work the string needs a character to replace
        myMasterIn.setCharAt(idx, (char)Wire.read() );    // update string
        idx ++;
    }

      Particle.publish("I2C from slave, length = "+String(myMasterIn.length()), myMasterIn, 60, PRIVATE);
    
}



void mySPI(){
    
    
    
}


void loop(){
    myUart();
    myI2C();
   
 //   mySPI();
 delay(4000);
    
    
}

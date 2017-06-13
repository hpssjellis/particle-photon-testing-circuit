// Photon Tester
// By Jeremy Ellis June 2017
// Twitter @rocksetta
// MIT license
// Use at your own risk!


// Master working photon 
// Slave unknown photon
// connect GND to GND
// on Master TX to slave RX
// On Master RX to slave TX


String myUartSlaveOut = "From uART Slave";
String myUartFromMaster;
int idu;


void setup() {
    Serial1.begin(9600);  // only if using this photon as a slave?
    Particle.publish("uART Serial1 Slave started", "On TX and RX", 60, PRIVATE);
    delay(1000);
    
}


void loop() {



      
    if (Serial1.available() > 0) {
        Serial1.write(myUartSlaveOut);   // send from uart master to slave
       
        int idu = 0;
        myUartFromMaster = "";

        while(Serial1.available()){   

            myUartFromMaster += 'H';   // for setCharAt to work the string needs a character to replace
            myUartFromMaster.setCharAt(idu, (char)Serial1.read() );    // update string
            idu ++;
        } 
    }
       
    Particle.publish("Sent From Slave = " + myUartSlaveOut  , "Received from Master = " + myUartFromMaster, 60, PRIVATE);
    delay(1000); 
    
}    










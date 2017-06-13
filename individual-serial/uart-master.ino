// Photon Tester Working Msater Photon
// By Jeremy Ellis June 2017
// Twitter @rocksetta
// MIT license
// Use at your own risk!

    // Master working photon 
    // Slave unknown photon
    // uART connectivity
    // connect GND to GND
    // 3V3 to 3V3
    // on Master TX to slave RX
    // On Master RX to slave TX
 
 
int x = 4;
String myUartMasterOut = "From uART Master";
String myUARTSlaveIn;
    

void setup() {
    Serial1.begin(9600);  // uART start TX, RX
    Particle.publish("uART Serial1 Master started", "On TX and RX", 60, PRIVATE);
    delay(1000);
    
    
}

void loop(){
  
      
    if (Serial1.available() > 0) {
        Serial1.write(myUartMasterOut);   // send from uart master to slave
       
        int idu = 0;
        myUARTSlaveIn = "";

        while(Serial1.available()){   // receive from uart slave

            myUARTSlaveIn += 'H';   // for setCharAt to work the string needs a character to replace
            myUARTSlaveIn.setCharAt(idu, (char)Serial1.read() );    // update string
            idu ++;
        }  
    }   

    Particle.publish("Sent From Master = " + myUartMasterOut , "Received from Slave = " + myUARTSlaveIn, 60, PRIVATE);
    delay(4000);
    
}

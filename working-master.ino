// Photon Tester Working Msater Photon
// By Jeremy Ellis June 2017
// MIT license




    
    // Master working photon 
    // Slave unknown photon
    // connect GND to GND
    // on Master TX to slave RX
    // On Master RX to slave TX
    


void setup() {
    Serial1.begin(9600);


}

void loop() {

    
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

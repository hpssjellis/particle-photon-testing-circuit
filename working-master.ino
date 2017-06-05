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
    Serial1.write('A');
    
    if (Serial1.available() > 0) {
        int incomingFromSlave = Serial.read();
        if (incomingFromSlave == 'B') {  
            Particle.publish("uART Serial working", String(incomingFromSlave), 60, PRIVATE);
        } 
    }
}

void loop() {


}

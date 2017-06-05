// Photon Tester Working Msater Photon
// By Jeremy Ellis June 2017
// MIT license




    
    // Master working photon 
    // Slave unknown photon
    // connect GND to GND
    // on Master TX to slave RX
    // On Master RX to slave TX
    


void setup() {
    Serial.begin(9600);
    Serial.print('H');
  
  
    Wire.beginTransmission(0); // transmit to device #9
    Wire.write('I');         

}

void loop() {


}

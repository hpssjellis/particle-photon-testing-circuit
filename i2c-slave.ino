uint8_t data[8];
int idx;

void receiveEvent(int numOfBytes) {
    idx = 0;
    while (Wire.available()) { 
        data[idx++] = (uint8_t)Wire.read();       
  } 
}


void setup() {
   // Serial.begin(9600);
    Wire.begin(8);
    Wire.onReceive(receiveEvent);
    pinMode(D7,OUTPUT);

}

void loop() {            
    Particle.publish("I2C received",String(idx),60,PRIVATE);
        delay(2000);
    if (idx != 0) {
        digitalWrite(D7,HIGH);
        //Serial.print("RX (");
       // Serial.print(idx);
        //Serial.print("): ");

        for(int i=0;i<idx;i++) {
           //Serial.println(data[i],HEX);  
        }
        
            Particle.publish("I2C data",String(data[0])+String(data[1])+String(data[2])+String(data[3])+String(data[4])+String(data[5])+String(data[6])+String(data[7]),60,PRIVATE);
            delay(2000);
        idx = 0;
        digitalWrite(D7,LOW);
    }


}

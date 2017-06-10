
int idx;


String myOut = "________________________________"; // Note: 32 chars Max string read 

void setup() {
   // Serial.begin(9600);
    Wire.begin(8);
    Wire.onReceive(receiveEvent);
    pinMode(D7,OUTPUT);

}

void receiveEvent(int numOfBytes) {
    idx = 0;
    while (Wire.available()) { 
        
        myOut.setCharAt(idx, (char)Wire.read() );  
        idx ++;
    } 
}



void loop() {            
    Particle.publish("I2C receiving wait 10 (s)",String(idx),60,PRIVATE);
    delay(10000);
    if (idx != 0) {
        digitalWrite(D7,HIGH);
        Particle.publish("I2C data better",String(myOut),60,PRIVATE);
        delay(1000);
        idx = 0;
        digitalWrite(D7,LOW);
    }


}

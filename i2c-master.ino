uint8_t val = 0;

void setup() {
    Wire.begin();
    pinMode(D7,OUTPUT);
}

void loop() {
    delay(1000);
    digitalWrite(D7,HIGH);
    Wire.beginTransmission(8);
    Wire.write(&val,1);
    Wire.endTransmission();
    val++;
    delay(20);
    digitalWrite(D7,LOW);
    
        Particle.publish("I2C sent",String(val),60,PRIVATE);
    delay(1000);
    
}

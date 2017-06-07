
String myString ;

void setup() {
    Wire.begin();
    pinMode(D7,OUTPUT);
}

void loop() {
    delay(10000);
    
    digitalWrite(D7,HIGH);
    Wire.beginTransmission(8);
    
    // only sends 32 characters but you can try more
    myString = "123456789012345678901234567890123456";
    Wire.write(myString);
    Wire.endTransmission();

    delay(20);
    digitalWrite(D7,LOW);
    Particle.publish("I2C sent, wait 10 (s)", myString ,60,PRIVATE);
    
    
}

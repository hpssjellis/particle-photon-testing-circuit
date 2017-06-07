uint8_t val = 0;
String myString ;

void setup() {
    Wire.begin();
    pinMode(D7,OUTPUT);
}

void loop() {
    delay(10000);
    digitalWrite(D7,HIGH);
    Wire.beginTransmission(8);
    //Wire.write(&val,1);
    myString = "12345678901234567890123456789012";
    Wire.write(myString);

    Wire.endTransmission();
    val++;
    delay(20);
    digitalWrite(D7,LOW);
    
    Particle.publish("I2C sent", myString ,60,PRIVATE);
    
    
}

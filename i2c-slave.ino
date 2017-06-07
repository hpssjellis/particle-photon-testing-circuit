//uint8_t data[8];
int idx;
//char myIn[8];
//String myOut = "____________________";
String myOut = "________________________________";

void receiveEvent(int numOfBytes) {
    idx = -1;
    while (Wire.available()) { 
        idx ++;
       // data[idx++] = (uint8_t)Wire.read();
         //myIn[idx] = (char)Wire.read();  
         //char wow = (char)Wire.read();  
       //myOut.setCharAt(idx, myIn[idx]);
       
        myOut.setCharAt(idx, (char)Wire.read() );  
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
        delay(10000);
    if (idx != 0) {
        digitalWrite(D7,HIGH);

        
            //Particle.publish("I2C data",String(myIn[0])+String(myIn[1])+String(myIn[2])+String(myIn[3])+String(myIn[4]),60,PRIVATE);
            //delay(2000);  
            Particle.publish("I2C data better",String(myOut),60,PRIVATE);
            delay(1000);
        idx = 0;
        digitalWrite(D7,LOW);
    }


}

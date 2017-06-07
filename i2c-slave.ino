// Include the required Wire library for I2C<br>#include <Wire.h>
int LED = D7;
int x = 0;
void setup() {
  // Define the LED pin as Output
  pinMode (LED, OUTPUT);
  // Start the I2C Bus as Slave on address 9
  Wire.begin(9); 
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
}
void receiveEvent(int bytes) {
  x = Wire.read();    // read one character from the I2C
}
void loop() {
  //If value received is 0 blink LED for 200 ms
  if (x == 0) {
  
        Particle.publish("I2C", String(x), 60, PRIVATE);
    delay(2000);
  }
  //If value received is 3 blink LED for 400 ms
  if (x == 3) {
  
        Particle.publish("I2C", String(x), 60, PRIVATE);
    delay(2000);
  }
}

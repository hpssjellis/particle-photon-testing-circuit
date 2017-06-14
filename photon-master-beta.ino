// Photon Tester Working Msater Photon
// By Jeremy Ellis June 2017
// MIT license
// Twitter @rocksetta
// Github   https://github.com/hpssjellis/particle-photon-testing-circuit
// Use at your own risk!

    // Photon to Photon uArt Setup
    // 3V3 Master to 3V3 Slave
    // Master working photon 
    // Slave unknown photon
    // connect GND to GND
    // on Master TX to slave RX
    // On Master RX to slave TX
    
    // Photon to Photon I2C setup
    // 3V3 Master to 3V3 Slave
    // GND master to GND slave
    // D0 (SDA = data) on master to D0 on slave
    // D1 (SCL = clock) on Master to D1 on slave
    // pullup 4.7 K ohm resistor from D0 to 3V3
    // pullup 4.7 K ohm resistor from D1 to 3V3


String uArtMasterSent  = "Bad";
String i2cMasterSent   = "Bad";
String spiMasterSent   = "Bad";







// uART gloabl variables
int x = 4;
String myUartMasterOut = "From uART Master";
String myUARTSlaveIn;
        



// I2C Global Variables
int idx;
String myI2CSlaveIn; // Note: 32 chars Max string read 
String myI2CMasterOut = "I2C from Master"; 



// Global SPI Variables
const unsigned long SEND_PERIOD_MS = 10000;
const int SS_PIN = A2;    // should be defined beofre setup
const size_t NUM_VALUES = 32;

unsigned long lastSend = 0;
uint32_t rcvdValues[NUM_VALUES];
uint32_t sendValues[NUM_VALUES];

String myMasterSent = "Hello to Slave";
String mySlaveSent ;





void setup() {
    Serial1.begin(9600);  // uART start TX, RX
    Wire.begin();         // I2C start DO, D1 
    SPI.begin(SPI_MODE_MASTER, SS_PIN);    // SPI start A2-A5
}
    


void myUart() {
  
    if (Serial1.available() > 0) {
        Serial1.write(myUartMasterOut);   // send from uart master to slave
       
        int idu = 0;
        myUARTSlaveIn = "";

        while(Serial1.available()){   // receive from uart slave

            myUARTSlaveIn += 'H';   // for setCharAt to work the string needs a character to replace
            myUARTSlaveIn.setCharAt(idu, (char)Serial1.read() );    // update string
            idu ++;
        }  
    }   

    Particle.publish("Sent From Master = " + myUartMasterOut , "Received from Slave = " + myUARTSlaveIn, 60, PRIVATE);
    delay(4000);
    
}    
  
    



void myI2C(){
    
    Wire.beginTransmission(8); // transmit to device #8   can be up to 128 devices?
    Wire.write(myI2CMasterOut);  // only sends 32 characters but you can try more
    Wire.endTransmission();

    Particle.publish("I2C Master sent", myI2CMasterOut, 60, PRIVATE);
    delay(1000);  
    
    

    Wire.requestFrom(8, 32);    // from slave #8 request MAX 32 reduce it if you know how many
  
    myI2CSlaveIn = "";
    idx = 0;
    while (Wire.available()) { 
       myI2CSlaveIn +="H";    // setCharAt needs a character to be able to replace it!
        myI2CSlaveIn.setCharAt(idx, (char)Wire.read() );  
        idx ++;
    }  

    
    Particle.publish("I2C Master sent =" + myI2CMasterOut,"I2C received from Slave = " + myI2CSlaveIn , 60, PRIVATE);
    delay(5000);   
  
}


void mySPI(){
    
  if (millis() - lastSend >= SEND_PERIOD_MS) {
		lastSend = millis();

		digitalWrite(SS_PIN, LOW);

		for(size_t ii = 0; ii < NUM_VALUES; ii++) {
			sendValues[ii] = (byte)myMasterSent[ii];
		}
		SPI.transfer(sendValues, rcvdValues, NUM_VALUES * sizeof(uint32_t), 0);
		digitalWrite(SS_PIN, HIGH);
	}
    mySlaveSent = "";
   	for(size_t ii = 0; ii < NUM_VALUES; ii++) {

		mySlaveSent  += 'H';   // for setCharAt to work the string needs a character to replace
        mySlaveSent.setCharAt(ii, (char)rcvdValues[ii] );    // update string
		
	} 
    
    
    Particle.publish( "Master sent " + myMasterSent, "Getting from Slave "+ mySlaveSent  , 60, PRIVATE);

	delay(9000);  
    
}


void loop(){
    
    myUart();
    myI2C();
    mySPI();
    
    delay(10000);
    
    
}

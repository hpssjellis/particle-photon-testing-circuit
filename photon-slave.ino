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

    // Photon to Photon SPI Setup
    // GND to GND
    // 3V3 to 3V3
    // A2 to A2   SS
    // A3 to A3   SCK
    // A4 to A4   MISO
    // A5 to A5   MOSI



//uART Global variables

String myUartSlaveOut = "From uART Slave";
String myUartFromMaster;
int idu;



// I2C Global Variables

int idx;

String myI2cMasterIn; // Note: 32 chars Max string read 
String myI2cSlaveOut = "I2C slave out."; // Note: 32 chars Max string read 




// SPI Global variables

void slaveSelect(uint8_t state);
void slaveCallback();

const int SS_PIN = A2;
const size_t NUM_VALUES = 32;

bool gotValue = false;
String sentToMaster="Hi from slave";
String gotFromMaster;

uint32_t rcvdValues[NUM_VALUES];
uint32_t sendValues[NUM_VALUES];







String mySlaveIn;

String uArtSlaveSent  = "Bad";
String i2cSlaveSent   = "Bad";
String spiSlaveSent   = "Bad";




void setup() {
    
    // Uart Setup
    Serial1.begin(9600);  // uART only if using this photon as a slave?
    Particle.publish("uART Serial1 Slave started", "On TX and RX", 60, PRIVATE);
    delay(1000);



    //I2C (Wire) Setup
    
    Wire.begin(8);
    Wire.onReceive(receiveEvent);   // so slave can receive data
    Wire.onRequest(requestEvent);   // so slave can send data

    

    //SPI Setup
    for(size_t ii = 0; ii < NUM_VALUES; ii++) {   
		sendValues[ii] = (byte)sentToMaster[ii];
	}

	SPI.onSelect(slaveSelect);
	SPI.begin(SPI_MODE_SLAVE, SS_PIN);
	
	
	

}



void myUART(){
    
    if (Serial1.available() > 0) {
        Serial1.write(myUartSlaveOut);   // send from uart master to slave
       
        int idu = 0;
        myUartFromMaster = "";

        while(Serial1.available()){   

            myUartFromMaster += 'H';   // for setCharAt to work the string needs a character to replace
            myUartFromMaster.setCharAt(idu, (char)Serial1.read() );    // update string
            idu ++;
        } 
    }
    
    if (myUartFromMaster == "From uART Master"){ uArtSlaveSent = "Good"; } else { uArtSlaveSent = "Bad"; }   
    Particle.publish("uART Slave Sent= " + myUartSlaveOut  , "uART from Master = " + myUartFromMaster, 60, PRIVATE);
    delay(1000); 
       
}    





// I2C Functions

void receiveEvent(int numOfBytes) {
    idx = 0;
    myI2cMasterIn = "";
    while (Wire.available()) { 
        myI2cMasterIn += "H";   // setCharAt needs a character to be able to replace it!
        myI2cMasterIn.setCharAt(idx, (char)Wire.read() );  
        idx ++;
    } 
}


void requestEvent() {
  Wire.write(myI2cSlaveOut);         // respond with message of 6 bytes as expected by master
}



void myI2C(){
    
    if (myI2cMasterIn == "I2C from Master"){ i2cSlaveSent  = "Good"; } else { i2cSlaveSent  = "Bad"; }
    Particle.publish("I2C slave sent = " + myI2cSlaveOut,"I2C from Master = " + myI2cMasterIn    ,60,PRIVATE);
    delay(5000);
 
}






// SPI functions

void slaveSelect(uint8_t state) {
	if (state) {
		SPI.transfer(sendValues, rcvdValues, NUM_VALUES * sizeof(uint32_t), slaveCallback);
	}
}

void slaveCallback() {
	gotValue = true;
}



void mySPI(){

  if (gotValue) {
		gotValue = false;
        gotFromMaster = "";

		for(size_t ii = 0; ii < NUM_VALUES; ii++) {
		    gotFromMaster  += 'H';   // for setCharAt to work the string needs a character to replace
            gotFromMaster.setCharAt(ii, (char)rcvdValues[ii] );    // update string

		}

    if (gotFromMaster == "Hello to Slave"){ spiSlaveSent = "Good"; } else { spiSlaveSent  = "Bad"; } 
	Particle.publish( "SPI Slave sent = "  + sentToMaster, "SPI from Master = " + gotFromMaster, 60, PRIVATE);
	delay(2000);   

	}   
}







void loop() {

    myUART();   

    myI2C();

    mySPI();
    
    Particle.publish( "uART Master to Slave",  uArtSlaveSent  ,  60, PRIVATE);
    delay(2000);
    
    Particle.publish( "I2C Master to Slave",  i2cSlaveSent  ,  60, PRIVATE);
    delay(2000);
    
    Particle.publish( "SPI Master To Slave", spiSlaveSent ,  60, PRIVATE);
    delay(2000);
    
    Particle.publish( "10 second wait", "---" ,  60, PRIVATE);    
    delay(10000);

}

// SPI-Slave.ino
// By Jeremy Ellis
// MIT license
// Use at your own risk!

    // Photon to Photon SPI Setup
    // GND to GND
    // 3V3 to 3V3
    // A2 to A2   SS
    // A3 to A3   SCK
    // A4 to A4   MISO
    // A5 to A5   MOSI


void slaveSelect(uint8_t state);
void slaveCallback();

const int SS_PIN = A2;
const size_t NUM_VALUES = 32;

bool gotValue = false;
String sentToMaster="Hi from slave";
String gotFromMaster;

uint32_t rcvdValues[NUM_VALUES];
uint32_t sendValues[NUM_VALUES];

void setup() {

	for(size_t ii = 0; ii < NUM_VALUES; ii++) {
		sendValues[ii] = (byte)sentToMaster[ii];
	}

	SPI.onSelect(slaveSelect);
	SPI.begin(SPI_MODE_SLAVE, SS_PIN);
}

void loop() {
	if (gotValue) {
		gotValue = false;
        gotFromMaster = "";

		for(size_t ii = 0; ii < NUM_VALUES; ii++) {
		    gotFromMaster  += 'H';   // for setCharAt to work the string needs a character to replace
            gotFromMaster.setCharAt(ii, (char)rcvdValues[ii] );    // update string

		}

	 	Particle.publish( "Slave sent "  + sentToMaster, "Getting from Master " + gotFromMaster, 60, PRIVATE);
	    delay(2000);   

	} 
}

void slaveSelect(uint8_t state) {
	if (state) {
		SPI.transfer(sendValues, rcvdValues, NUM_VALUES * sizeof(uint32_t), slaveCallback);
	}
}

void slaveCallback() {
	gotValue = true;
}

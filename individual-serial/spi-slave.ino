#include "Particle.h"

SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler;

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
//	Serial.begin(9600);

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
	//	Log.info("rcvdValues[0]=0x%lx rcvdValues[1]=0x%lx", rcvdValues[0], rcvdValues[1]);

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

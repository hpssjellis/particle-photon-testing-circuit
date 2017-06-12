#include "Particle.h"

SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler;

const unsigned long SEND_PERIOD_MS = 10000;
const int SS_PIN = A2;
const size_t NUM_VALUES = 32;

unsigned long lastSend = 0;
uint32_t rcvdValues[NUM_VALUES];
uint32_t sendValues[NUM_VALUES];

String MasterSend = "Hello to Slave";
String mySlaveSent ;


void setup() {
//	Serial.begin(9600);

	SPI.begin(SPI_MODE_MASTER, SS_PIN);
}

void loop() {
	if (millis() - lastSend >= SEND_PERIOD_MS) {
		lastSend = millis();

		digitalWrite(SS_PIN, LOW);

		for(size_t ii = 0; ii < NUM_VALUES; ii++) {
			sendValues[ii] = (byte)MasterSend[ii];
		}
	//	Log.info("sendValues[0]=0x%lx sendValues[1]=0x%lx", sendValues[0], sendValues[1]);

		SPI.transfer(sendValues, rcvdValues, NUM_VALUES * sizeof(uint32_t), 0);

	//	Log.info("rcvdValues[0]=0x%lx rcvdValues[1]=0x%lx", rcvdValues[0], rcvdValues[1]);

		digitalWrite(SS_PIN, HIGH);
	}
//	Particle.publish("sent", String(sendValues[0],DEC) + ", "+String(sendValues[1],DEC), 60, PRIVATE);
    mySlaveSent = "";
   	for(size_t ii = 0; ii < NUM_VALUES; ii++) {

		mySlaveSent  += 'H';   // for setCharAt to work the string needs a character to replace
        mySlaveSent.setCharAt(ii, (char)rcvdValues[ii] );    // update string

		
	} 
    
    
    Particle.publish( "Master sent "+MasterSend, "Getting from Slave "+mySlaveSent  , 60, PRIVATE);

	delay(9000);
}
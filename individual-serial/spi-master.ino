// SPI-Master.ino
// By Jeremy Ellis
// MIT license
// Use at your own risk!

const unsigned long SEND_PERIOD_MS = 10000;
const int SS_PIN = A2;
const size_t NUM_VALUES = 32;

unsigned long lastSend = 0;
uint32_t rcvdValues[NUM_VALUES];
uint32_t sendValues[NUM_VALUES];

String myMasterSent = "Hello to Slave";
String mySlaveSent ;

void setup() {

	SPI.begin(SPI_MODE_MASTER, SS_PIN);
}

void loop() {
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

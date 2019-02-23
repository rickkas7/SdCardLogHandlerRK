#include "Particle.h"

#include "SdFat.h"
#include "SdCardLogHandlerRK.h"

SYSTEM_THREAD(ENABLED);

const int SD_CHIP_SELECT = D5;
SdFat sd;


// API change in 0.1.0: You must specify the size of the log handler buffer and call both logHandler.setup() and logHandler.loop()!
SdCardLogHandler<2048> logHandler(sd, SD_CHIP_SELECT, SPI_FULL_SPEED);

size_t counter = 0;
unsigned long lastCounterUpdate = 0;

void setup() {
	Serial.begin(9600);

	// You must call logHandler.setup() from setup()!
	logHandler.setup();
}

void loop() {
	// You must call logHandler.loop() from loop()!
	logHandler.loop();

	if (millis() - lastCounterUpdate >= 1000) {
		lastCounterUpdate = millis();
		Log.info("testing counter=%d", counter++);
	}
}

#include "Particle.h"

#include "SdFat.h"
#include "SdCardLogHandlerRK.h"

SYSTEM_THREAD(ENABLED);

const int SD_CHIP_SELECT = D5;
SdFat sd;

// Only log errors and app.sd info level log messages to the SD card
// API change in 0.1.0: You must specify the size of the log handler buffer and call both logHandler.setup() and logHandler.loop()!
SdCardLogHandler<2048> sdLogHandler(sd, SD_CHIP_SELECT, SPI_FULL_SPEED, LOG_LEVEL_ERROR, {
	{ "app.sd", LOG_LEVEL_INFO }
});
// Turn off serial logging in the SdCardLogHandler to avoid logging twice
STARTUP(sdLogHandler.withNoSerialLogging());

// Use LogToSD.info() instead of Log.info(), etc. to write to the SD card
Logger LogToSD("app.sd");

// Log everything to Serial
SerialLogHandler serialLogHandler;


size_t counter = 0;
unsigned long lastCounterUpdate = 0;

void setup() {
	Serial.begin(9600);

	// You must call logHandler.setup() from setup()!
	sdLogHandler.setup();
}

void loop() {
	if (millis() - lastCounterUpdate >= 1000) {
		lastCounterUpdate = millis();
		Log.info("testing counter=%d", counter++);
		LogToSD.info("write to SD counter=%d", counter++);
	}

	// You must call logHandler.loop() from loop()!
	sdLogHandler.loop();
}

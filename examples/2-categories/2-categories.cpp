#include "Particle.h"

#include "SdFat.h"
#include "SdCardLogHandlerRK.h"

SYSTEM_THREAD(ENABLED);

const int SD_CHIP_SELECT = A2;
SdFat sd;

// Only log errors and app.sd info level log messages to the SD card
SdCardLogHandler sdLogHandler(sd, SD_CHIP_SELECT, SPI_FULL_SPEED, LOG_LEVEL_ERROR, {
	{ "app.sd", LOG_LEVEL_INFO }
});
// Turn off serial logging in the SdCardLogHandler to avoid logging twice
STARTUP(sdLogHandler.withNoSerialLogging());

// Use LogToSD.info() instead of Log.info(), etc. to write to the SD card
Logger LogToSD("app.sd");

// Log everything to Serial
SerialLogHandler serialLogHandler;


size_t counter = 0;

void setup() {
	Serial.begin(9600);
	sdLogHandler.setup();
}

void loop() {
	Log.info("testing counter=%d", counter++);
	LogToSD.info("write to SD counter=%d", counter++);

	delay(1000);
}

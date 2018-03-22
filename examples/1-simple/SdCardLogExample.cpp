#include "Particle.h"

#include "SdFat.h"
#include "SdCardLogHandlerRK.h"

SYSTEM_THREAD(ENABLED);

const int SD_CHIP_SELECT = A2;
SdFat sd;

SdCardLogHandler logHandler(sd, SD_CHIP_SELECT, SPI_FULL_SPEED);

size_t counter = 0;

void setup() {
	Serial.begin(9600);

}

void loop() {
	Log.info("testing counter=%d", counter++);
	delay(1000);
}

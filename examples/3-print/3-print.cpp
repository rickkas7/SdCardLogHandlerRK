#include "Particle.h"

#include "SdCardLogHandlerRK.h"

SYSTEM_THREAD(ENABLED);

// The SD card CS pin on the Adafruit AdaLogger FeatherWing is D5.
const int SD_CHIP_SELECT = D5;
SdFat sd;

SdCardPrintHandler printToCard(sd, SD_CHIP_SELECT, SPI_FULL_SPEED);

size_t counter = 0;

void setup() {
	Serial.begin();
}

void loop() {
	printToCard.printlnf("testing counter=%d", counter++);
	delay(1000);
}

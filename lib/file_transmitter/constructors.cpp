#include "file_transmitter.h"
file_transmitter::file_transmitter()
{
	Serial.flush();
	while (Serial.available() > 0)
	{
		Serial.read();
	}
	start_delay = DEFAULT_START_DELAY;
}

#pragma once
// Comands.h is going to be responsible for holding formatted
#include "commands.h"
#include "error_codes.h"
// Configs allow experiments on best default values
#include "default_values_and_configs.h"
#include <SD.h>
#include <Arduino.h>
#include <string.h>
#include "SPIFFS.h"

class file_transmitter
{		// The class
public: // Access specifier
	int start_delay;
	file_transmitter();

	// Return values will be error codes
	int init_connection();
	int init_server();

private:
};

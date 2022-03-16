#include "file_transmitter.h"
unsigned char init_listen();

unsigned char init_listen()
{
	while (true)
	{
		if (Serial.available() > 0)
		{
			return Serial.read();
		}
	}
}
unsigned char syn_response(unsigned char syn);
unsigned char syn_response(unsigned char syn)
{
	unsigned char ack_to_client;
	ack_to_client = 11; // Replace this with something
	Serial.print(ack_to_client);
	Serial.print(syn + 1);
	return ack_to_client;
}

unsigned char check_final_ack(unsigned char ack)
{
	unsigned char response = init_listen();
	if (response == (ack + 1))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
unsigned char announce_server(unsigned char start, int delay)
{
	while (true)
	{
		Serial.print(start);
		Serial.flush();
		unsigned char ack;
		ack = Serial.read();
	}
}

int file_transmitter::init_server()
{
	Serial.flush();
	while (Serial.available() > 0)
	{
		Serial.read();
	}

	unsigned char syn;
	unsigned char client_response;
	int bytes_available;
	unsigned char ack_to_client;
	unsigned char loop_count = 0;
	unsigned char state = 0;
	unsigned char client_ack;
	unsigned char reques_is_valid;
	announce_server(0, 10);						   // Client has declared it is looking to connect
	LISTEN: syn = init_listen();						   // Server is listening for a connection
	if(syn==255){ // You can't increment 255 to make a valid ack
		return NORMAL_EXIT; // 255 is the code to ex it without establishing a connection
	}
	client_ack = syn_response(syn);				   // Takes the client's syn and creates an ack. Sends both.
	request_is_valid = check_final_ack(client_ack) // Waits for the client's final acknowledgement and checks if it's valid
		if (request_is_valid == 1)
	{
		Serial.print(255); // in this system 255 is the error code for a failed request
		goto LISTEN; // restart the listener.
	}
	// Server is sending it's syn-ack
	/*
	while (true)
	{

		// delay(100);
		bytes_available = Serial.available();
		// Serial.print(loop_count);
		// Serial.print(loop_count);
		while (true)
		{
			bytes_available = Serial.available();
			if (bytes_available >= 1)
			{
				syn = Serial.read();
				state = 1;
				break;
			}
			// Serial.print(1);
			// delay(5);
		}*/
	// Clear the input and output buffers before sending

	// Serial.flush();
	/*
	while (Serial.available() > 0)
	{
		Serial.read();
	}
	*/
	/*
			Serial.print(syn + 1);
			// Serial.print(syn + 1);
			Serial.flush();
			while (true)
			{
				bytes_available = Serial.available();
				if (bytes_available == 1)
				{
					client_response = Serial.read();
					// break;
					//  Check if it matches
					return NORMAL_EXIT;
				}
				// Serial.print(1);
				delay(5);
			}
			*/

	/*
	 while (true)
	 {
		 bytes_available = Serial.available();
		 if (bytes_available == 2)
		 {
			 syn = Serial.read();
			 break;
		 }
		 // Serial.print(1);
		 delay(5);
	 }
	 */
	/*
			if (bytes_available >= 1)
			{
				// Serial.print(Serial.read());

				// Serial.print(syn + 1);
				syn = 0;
				// Serial.print(syn);
				Serial.print(syn + 1);
				Serial.print(syn + 2);
				// Serial.print('a');
				syn = 11;
				// Serial.print(syn);
				Serial.flush();
				// Serial.print(11);
				// ack_to_client = 11;
				//  Serial.print(loop_count);
				//   Serial.print(loop_count);
			}
			bytes_available = Serial.available();
			while (
				bytes_available < 1)
			{
				bytes_available = Serial.available();
			}
			client_response = 11;
			// Serial.read();
			if (client_response == ack_to_client + 1)
			{
				return NORMAL_EXIT;
			}

			if (loop_count = 253)
			{
				loop_count == 0;
			}
			else
			{
				loop_count++;
			}
			*/
}

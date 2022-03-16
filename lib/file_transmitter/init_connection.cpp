#include "file_transmitter.h"
int file_transmitter::init_connection()
{
	// cur_syn is incremented every loop; right now it starts at zero
	uint8_t cur_syn = DEFAULT_START_SYN;
	// defines how long the wait on this side will be between connection attempts
	int wait_time = DEFAULT_START_DELAY;
	// these
	uint8_t received_seq;
	uint8_t received_ack;
	// uint8_t ack_to_send;
	// uint8_t cur_seq;
	//  same as cur_syn after cur_syn is sent in the first part of the loop
	uint8_t sent_syn;
	// Holds the response from the desktop
	uint8_t byte_arr[2];
	int loop_count;
	while (true)
	{
		// Ensure that all data received will come from current init
	START:
		Serial.flush();
		while (Serial.available() > 0)
		{
			Serial.read();
		}
		Serial.print(cur_syn);
		sent_syn = cur_syn;
		Serial.flush();
		// delay(50);
		//  if the default should be modified that code goes here
		//  delay(wait_time); // The receiver may sen things back ASAP
		//  These bytes must be a response to the last connection request
		// delay(50);

		while (Serial.available() < 2)
		{
			delay(1);
			loop_count++;
			if (loop_count == 1000)
			{
				goto START;
			}
		} /*
		 if (Serial.available() > 2)
		 {
			 goto START;
		 }
		 */
		if (Serial.available() == 2)
		{

			Serial.readBytes(byte_arr, 2);
			received_ack = byte_arr[1];
			received_seq = byte_arr[0];
			if (received_ack == (sent_syn + 1))
			{
				// cur_seq = received_syn + 1; // This can go if not used.
				// cur_ack = ack_to_send + 1;
				//   Serial.print(cur_seq);
				//   The final ack is the received ack + 1 ;
				// Serial.print(received_seq + 1);
				Serial.print(received_ack);
				Serial.flush();
				return NORMAL_EXIT;
			}
		}
		else if (cur_syn == 253) // received ack then 254, final ack = 255. That prevents overflow in any loop.
		{
			cur_syn = 0;
		}
		else
		{
			cur_syn++;
		}

		/*
			if (Serial.available() > 1)
			{
				// Serial.readBytes(byte_arr, 2);
				// received_ack = byte_arr[1];
				// received_seq = byte_arr[0]; // These could be backwards...

				// This is checking if the "server" sent the correct ack bit i.e. sent ack + 1
				// The last
				if (received_ack == (sent_syn + 1))
				{
					// cur_seq = received_syn + 1; // This can go if not used.
					// cur_ack = ack_to_send + 1;
					//   Serial.print(cur_seq);
					//   The final ack is the received ack + 1 ;
					Serial.print(received_seq + 1);
					Serial.print(received_ack);
					Serial.flush();
					return NORMAL_EXIT;
				}
			}
			// The  desktop script did not respond to the request connection
			else
			{
				if (cur_syn == MAX_INIT_LOOPS && false)
				{
					// This will be removed once this is all working, or removed by the compiler as unreachable
					if (DEBUG)
					{
						Serial.println("Excess loop error in init_connection");
					}
					return EXCESS_INIT_LOOPS_ERROR;
				}
				else if (cur_syn == 253) // received ack then 254, final ack = 255. That prevents overflow in any loop.
				{
					cur_syn = 0;
				}
				else
				{
					cur_syn++;
				}

			}*/
	}
}
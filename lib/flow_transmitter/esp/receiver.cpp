#include "receiver.h"
char Receiver::listen(int listen_time)
{

	unsigned long temp_expire_time = expire_time;
	timer_reset(listen_time);
	char read_byte;
	while (timer_not_expired())
	{
		if (Serial.available() != 0)
		{
			read_byte = Serial.read();

			expire_time = temp_expire_time;
			return read_byte;
			// return read_byte;
		}
	}
	return '*';
}
int read_to_buffer(int size, int offset)
{
	//serial.setTimeout(3000);
	int numRead;
	if(offset ==CUR_OFFEST){
		numRead = Serial.readBytes((curBufferOffset+ bigBuffer), size);
	}
	numRead = Serial.readBytes( bigBuffer+offset, size);
}
void setBuffer(void * buff){
	
	bigBuffer= buff;
}
boolean Receiver::listen_match(char sent, char received, int listen_time)
{
	Serial.print(sent);
	// Serial.print("c");

	return true;
	if (listen(listen_time) == received)
	{
		Serial.print("c");
		return true;
	}
	else
	{
		return false;
	}
	// return (received == listen(listen_time));
}
int Receiver::send_int(int value)
{
	int *z = &value;
	void *y = (void *)z;
	const unsigned char *q = (const unsigned char *)y;
	// const unsigned char *buf = (void*)&rec;

	// Serial.print(rec);
	Serial.write(q, 4);
	return 0;
}
void Receiver::timer_reset(int max_time)
{
	expire_time = millis() + max_time;
}

boolean Receiver::timer_not_expired()
{
	if (millis() < expire_time)
	{
		return true;
	}
	return false;
}

int Receiver::init_connection(int max_time, int repeat_time)
{
	timer_reset(max_time);
	int state = 0;
	char received;
	int start_time = millis();
	// int listen_time;
	int announce_time = 20;
announce_esp:
	while ((start_time + max_time) > millis())
	{
		Serial.print('a');

		received = listen(announce_time);
		if (received == '*')
		{
			continue;
		}
		if (received == 'b')
		{
			break;
			// Serial.flush();
			//  run_server(max_time);
			// Serial.print("a");
			// Serial.print(
		}
	}

	start_time = millis();

	while ((start_time + max_time) > millis())
	{
		Serial.print("c");
		received = listen(repeat_time);
		if (received == '*')
		{
			goto announce_esp;
			continue;
		}
		if (received == 'd')
		{
			Serial.print("e");
			return 0;

			// Serial.flush();
			//  run_server(max_time);
			// Serial.print("a");
			// Serial.print(
		}
	}

	// Serial.print("a");
	// Serial.print("c");

	return -1;
}

boolean Receiver::command_not_valid(char input)
{
	return !(('O' == input) || ('P' == input) || ('+' == input) || ('E' == input));
}
unsigned int Receiver::readInt(int listen_time)
{
	// unsigned char bytesRead[4];
	//  Serial.readBytes(bytesRead, 4);
	// unsigned char b1 = listen(listen_time);
	// unsigned char b2 = listen(listen_time);
	// unsigned char b3 = listen(listen_time);
	// unsigned char b4 = listen(listen_time);
	unsigned int sum = 0;
	unsigned char cur_byte;
	unsigned int cur_int;
	for (int i = 0; i < 4; i++)
	{
		cur_byte = listen(listen_time);
		cur_int = (int)cur_byte;
		cur_int = cur_int << (24 - (i * 8));
		sum = sum + cur_int;
	}
	// unsigned int input = (bytesRead[0] << 24 | bytesRead[1] << 16 | bytesRead[2] << 8 | bytesRead[1] << bytesRead[0]);
	return sum;
}

char Receiver::run_server(int server_timeout, int listen_timeout)
{
	char input;
	timer_reset(server_timeout);
	int start_time = millis();
	int last_input_time;
	while (millis() < (start_time + server_timeout))
	{
		// Serial.print("q");
		input = listen(listen_timeout);
		if (input == '*' || command_not_valid(input))
		{
			Serial.print("*");
			continue;
		}
		else
		{
			start_time = millis();
		}

		switch (input)
		{
		case 'P':
			Serial.print("p");
			continue;
		case 'O':
			Serial.print("o");
			// Serial.print("o");
			cur_file_name = Serial.readString();

			/// const char* real_file_name = "/spiffs" + file_name;
			// int length_file;
			cur_file_ptr = fopen(cur_file_name.c_str(), "wb");
			Serial.print("!");

			// Going to need to make some changes here using uart lib directly
			// String file_name = Serial.readString(); //
			// open file
			// send success if file opened successfully
			continue;
		/*
		case 'C':
			cur_file_name = Serial.readString();
		*/
		case 'E': // Case exit
			Serial.write('E');
			return '!';
		};
	}
	return '*';
}

// This part is literally another library that's been copy and pasted into the file.

#if defined(PROGMEM)
#define FLASH_PROGMEM PROGMEM
#define FLASH_READ_DWORD(x) (pgm_read_dword_near(x))
#else
#define FLASH_PROGMEM
#define FLASH_READ_DWORD(x) (*(uint32_t *)(x))
#endif

static const uint32_t crc32_table[] FLASH_PROGMEM = {
	0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
	0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
	0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
	0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c};

CRC32::CRC32()
{
	reset();
}

void CRC32::reset()
{
	_state = ~0L;
}

void CRC32::update(const uint8_t &data)
{
	// via http://forum.arduino.cc/index.php?topic=91179.0
	uint8_t tbl_idx = 0;

	tbl_idx = _state ^ (data >> (0 * 4));
	_state = FLASH_READ_DWORD(crc32_table + (tbl_idx & 0x0f)) ^ (_state >> 4);
	tbl_idx = _state ^ (data >> (1 * 4));
	_state = FLASH_READ_DWORD(crc32_table + (tbl_idx & 0x0f)) ^ (_state >> 4);
}

uint32_t CRC32::finalize() const
{
	return ~_state;
}
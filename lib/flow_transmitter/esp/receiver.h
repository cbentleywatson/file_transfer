#pragma once
#include <Arduino.h>
#define DEFAULT_SERVER_TIMEOUT 20000
#define DEFAULT_SERVER_LISTEN_TIMEOUT 100
#define CUR_OFFEST
/*
struct packet_header
{
	unsigned int packet_number;
	unsigned int length;
	unsigned int checksum;
};
*/
class Receiver
{
public:
	unsigned long time_last;
	unsigned long expire_time;
	void timer_reset(int max_time);
	unsigned int readInt(int listen_time);
	int send_int(int value);
	String cur_file_name;
	FILE *cur_file_ptr;
	void *big_buffer; 
	int curBufferOffset;
	// unsigned char * block;
	// int readInto(size); // read the bytes into the current file offset.  
	//int init_connection();
	int init_connection(int max_time, int repeat_time);
	char listen(int listen_time);
	boolean command_not_valid(char input);
	char run_server(int server_timeout, int listen_timeout);
	boolean listen_match(char sent, char received, int listen_time);
	boolean timer_not_expired(void);
};

////////////////////////
//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//



/// \brief A class for calculating the CRC32 checksum from arbitrary data.
/// \sa http://forum.arduino.cc/index.php?topic=91179.0
class CRC32
{
public:
	/// \brief Initialize an empty CRC32 checksum.
	CRC32();

	/// \brief Reset the checksum claculation.
	void reset();

	/// \brief Update the current checksum caclulation with the given data.
	/// \param data The data to add to the checksum.
	void update(const uint8_t &data);

	/// \brief Update the current checksum caclulation with the given data.
	/// \tparam Type The data type to read.
	/// \param data The data to add to the checksum.
	template <typename Type>
	void update(const Type &data)
	{
		update(&data, 1);
	}

	/// \brief Update the current checksum caclulation with the given data.
	/// \tparam Type The data type to read.
	/// \param data The array to add to the checksum.
	/// \param size Size of the array to add.
	template <typename Type>
	void update(const Type *data, size_t size)
	{
		size_t nBytes = size * sizeof(Type);
		const uint8_t *pData = (const uint8_t *)data;

		for (size_t i = 0; i < nBytes; i++)
		{
			update(pData[i]);
		}
	}

	/// \returns the caclulated checksum.
	uint32_t finalize() const;

	/// \brief Calculate the checksum of an arbitrary data array.
	/// \tparam Type The data type to read.
	/// \param data A pointer to the data to add to the checksum.
	/// \param size The size of the data to add to the checksum.
	/// \returns the calculated checksum.
	template <typename Type>
	static uint32_t calculate(const Type *data, size_t size)
	{
		CRC32 crc;
		crc.update(data, size);
		return crc.finalize();
	}

private:
	/// \brief The internal checksum state.
	uint32_t _state = ~0L;
};

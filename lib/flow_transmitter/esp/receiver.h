#pragma once
#include <Arduino.h>
#define DEFAULT_SERVER_TIMEOUT 20000
#define DEFAULT_SERVER_LISTEN_TIMEOUT 100
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
	int init_connection();
	int init_connection(int max_time, int repeat_time);
	char listen(int listen_time);
	boolean command_not_valid(char input);
	char run_server(int server_timeout, int listen_timeout);
	boolean listen_match(char sent, char received, int listen_time);
	boolean timer_not_expired(void);
};
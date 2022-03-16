/*
listen(int length, int time_logout){
	unsigned long start =millis();
	while((Serial.available<length) && ((millis()-start)< time_logout ) ){
		;
	}
}
// Clear output with flush and then remove all of the responses with Serial.read()
// This function should really only be called once, when init starts
 void clear_buffers(unsigned long time_logout){
	Serial.flush();
	unsigned long start =millis();
	while( (millis()-start)< time_logout  ){
		if(Serial.available != 0){
			Serial.readString();
		}
	}
}

char listen( int time_logout){
	length =1;
	unsigned long start =millis();
	// Busy wait until something is found or the listen times out
	while((Serial.available<length) && ((millis()-start)< time_logout ) ){
		;
	}
	int available = Serial.available();
	if(available ==0){
		return '*';
	}else{
		// malloc an array large enough to hold the target values;
		// Read the available bytes into that array
		// get the last (first?) byte
		// free the array
		// return the value
	}

}
*/

/*
char send_listen(char input, char target, int max_time, int wait_time){
	unsigned long start =millis();
	Serial.write(input);
	char out;
	bool indefinite= false;
	if(max_time ==-1){
		indefinite = true
	}
	// if indefinite is set, while will always be true and the loop wil run forever
	while( indefinite ||((millis()-start)<max_time) ){
		out =  listen(wait_time);
		if(out==target){
			return target;
		}else{
			Serial.write(input);
		}
	}
	return '*';
}
// makes the 
char synchronize(){
	clear_buffers();
	char client_response;
	// If the desktop script doesn't respond, stay put forever (for now, for testing)
	client_response = send_listen('a', 'b', -1, 100);
	// Once the script responds, it's all or nothing; either the entire synchronization works or the whole thing fails

	// Client response has to be b or something is wrong
	if(client_response != 'b'){
		return '*';
	}

	// repeat the process. 'c' is the final acknowledge in this simplified handshake;
	client_response = send_listen('b', 'c', 1500, 100);

	if((client_response == '*') ||(client_response != 'c')){
		return '*';
	}else{
		return client_response;
	}

}


*/
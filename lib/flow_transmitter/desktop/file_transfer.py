#from CONFIG_CONSTANTS import NORMAL_EXIT
import sys
from CONFIG_CONSTANTS import *
from transmitter import transmitter

test_transmitter = transmitter(MY_PORT)
#return_val = test_transmitter.start_session()
return_val = test_transmitter.five_part_init()
if(return_val == False):
	print("Connection initialization failed, no load")
	sys.exit(0)


# test functions. RUN_TESTS is controlled in  the CONFIG_CONSTANTS_FILE
if (RUN_TESTS):
	val = 1
	print("\nTesting read and write with val="+ str(val))
	test_transmitter.send_int(val)	
	# this is completed. DO NOT TOUCH
	print(test_transmitter.rec_int())
	
	val = 997
	print("\nTesting read and write with val="+ str(val))
	test_transmitter.send_int(val)	
	# this is completed. DO NOT TOUCH
	print(test_transmitter.rec_int())
	print("\nTesting ping")


	ping_val, ping_return =test_transmitter.ping()
	print("ping return: " + ping_return.decode('ascii'))
	if(ping_val):
		print("Test Transmitter ping function returned successfully. ping returned :" + ping_return.decode('ascii'))
	else:
		print("Test transmitter's ping function failed. Ping Returned " + ping_return.decode('ascii') )
		
	print("ping return: " + ping_return.decode('ascii'))
	if(ping_val):
		print("Test Transmitter ping function returned successfully. ping returned :" + ping_return.decode('ascii'))
	else:
		print("Test transmitter's ping function failed. Ping Returned " + ping_return.decode('ascii') )
		
	
	o_value =test_transmitter.open_esp_file("/sd/test1.b")

	print("Testing CRC 32")

# End of test functions

test_transmitter.close_and_exit()
"""
if return_val == NORMAL_EXIT:
	print("Successful seesion connection")
elif return_val == LISTEN_TIMEOUT_ERROR:
	print("Error code LISTEN_TIMEOUT_ERROR")
else :
	print("Unknown error")
"""
#from CONFIG_CONSTANTS import NORMAL_EXIT
from CONFIG_CONSTANTS import *
from transmitter import transmitter

test_transmitter = transmitter(MY_PORT)
#return_val = test_transmitter.start_session()
return_val = test_transmitter.start_server_session()
if return_val == NORMAL_EXIT:
	print("Successful seesion connection")
elif return_val == LISTEN_TIMEOUT_ERROR:
	print("Error code LISTEN_TIMEOUT_ERROR")
else :
	print("Unknown error")
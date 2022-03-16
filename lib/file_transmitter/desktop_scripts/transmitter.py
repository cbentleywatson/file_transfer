#import init_connection
from random import choice
from socket import timeout
from sre_constants import SUCCESS
import serial
import time
from serial import Serial
from  CONFIG_CONSTANTS import *
class transmitter:
	
	def __init__(self, port):
		print("file_transmitter initialized")
		self.ser = serial.Serial()
		self.ser.baudrate = 115200
		#ser.port = 'COM6'
		self.ser.port = port
		self.listen_timeout = DEFAULT_LISTEN_TIMEOUT
		self.wait_loop_timeout = 1
		self.ser.open()
		#this is the default value for MY COMPUTER remove it later
		#self.ser.port = '/dev/tty6'
	def start_session(self):
		#listen a while
		self.ser.reset_output_buffer()
		self.ser.reset_input_buffer()
		start = time.time()
		final_start =0
		time.sleep(.01)
		while(True):
			self.ser.timeout = 0
			#print("top of loop" )
			cur_bytes =self.ser.in_waiting
			while(self.ser.in_waiting==0):
				time.sleep(.01) 
			if  cur_bytes>= 1:
				client_syn =self.ser.read(1) 
				#print("BYTE found!")
				ord_client_syn = 0
				ord_client_syn = ord(client_syn)
				ack = choice(range(1, 253, 1))
				self.ser.write(client_syn)
				self.ser.write(ack)
				self.ser.flush()
				final_start= time.time()
				while(self.ser.in_waiting<1):
					time.sleep(.01)
					if(False and (time.time() - final_start >self.wait_loop_timeout)):
						break
				if(self.ser.in_waiting>0):			
					#print("final ack")
					self.ser.timeout = 1
					client_syn =self.ser.read(1)
					client_final_acknowledge = ord(client_syn)
					if(client_final_acknowledge == ack+1):
						time.sleep(.099)
						print("Found")	
						self.ser.flushInput
						self.ser.flushOutput
						return NORMAL_EXIT
					else:
						#print("Not Found")
						time.sleep(.01)
						self.ser.reset_input_buffer
						self.ser.reset_output_buffer
						continue
					
							
	def start_server_session(self):
		rList =[0]
		arr = bytes(rList)
		self.ser.reset_input_buffer
		self.ser.reset_output_buffer
		cur_bytes = 0
		syn = arr[0]
		while (True):
			#self.ser.write(arr[0])
			time.sleep(1)
			self.ser.reset_input_buffer
			self.ser.reset_output_buffer	
			self.ser.write(arr[0])
			
			#Serial.flush()
			#print("Writing syn to serial")
			#print(ord(syn))
			
			cur_bytes =self.ser.in_waiting
			#if(self.ser.in_waiting ==2):
			#	print 
			#
			# while(True):
			#	cur_bytes = self.ser.in_waiting
			#	if(cur_bytes==2):
			#		break
			print("Sending syn")
			

			if(cur_bytes >=2):
				print("Reading bytes")
				server_syn =self.ser.read(1) 
				server_ack =  self.ser.read(1) 
				#return NORMAL_EXIT
				self.ser.reset_input_buffer
				self.ser.reset_output_buffer	
				print("sent syn")
				#print(ord(arr[0]))
				print(syn)

				print("Server_syn")
				print(ord(server_syn))
				
				print("Server ack")
				print(ord(server_ack))
				print("")
				if(ord(server_ack) == syn+1):
					self.ser.write(server_ack) #server_ack is a stand in, I just want the final bite sent
					print("Final byte")
					return NORMAL_EXIT
			

			
			if(syn==253):
				syn =0
			else:
				syn = syn+1
			


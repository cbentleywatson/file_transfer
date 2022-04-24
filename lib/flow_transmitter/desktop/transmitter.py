#import init_connection
from operator import truediv
from random import choice
from socket import timeout
from sre_constants import SUCCESS
from sys import byteorder
import serial
import time
from serial import Serial
from binascii import crc32


from  CONFIG_CONSTANTS import *
class transmitter:
	
	def __init__(self, port):
		print("file_transmitter initialized")
		self.ser = serial.Serial()
		self.ser.baudrate = 115200
		#ser.port = 'COM6'
		self.ser.port = port
		self.listen_timeout = DEFAULT_LISTEN_TIMEOUT
		self.init_connection_timeout = 1000*DEFAULT_INIT_CONNECTION_TIMEOUT
		self.wait_loop_timeout = 1
		self.ser.open()
		self.expire_time =0
		self.last_value_read = b'~'
		self.transaction_wait_time = 1000
		
	


		self.fileContents = bytes("default_packet_content", 'ascii')
		self.fileSize = 0
		#packet data:
		self.fileOffset = 0
		self.packetMaxSize = 1024
		self.packetNumber = 0
		self.packet_data = bytes("default_packet_content", 'ascii')
		self.curPacketSize = 0
		self.curCRC = 0
		self.endIndex =0
		self.file_packets_remaining = False
		self.send_packet_timeout = 2
	def increment_packet(self):

		self.fileOffset = self.fileOffset + self.curPacketSize
		self.packetNumber= self.packetNumber + 1
		self.curPacketSize = min([self.packetMaxSize, (self.fileSize- self.fileOffset) ])
		self.endIndex = self.fileOffset + self.curPacketSize
		self.packet_data = self.fileContents[self.fileOffset:self.endIndex]
		self.curCRC = crc32(self.packet_data)
		
		
		# This means that the current packet should be process and then the system is finished
		if(self.endIndex== self.fileSize):
			#print("File Filled")
			self.file_packets_remaining = False 
		else:
			self.file_packets_remaining = True
	def reset_packets(self):
		self.fileOffset =0
		self.curPacketSize =0
		self.packet_data =b''
		self.curCRC = 0
		
		#self.blankPacket = {'num': 1, 'crc}
		#this is the default value for MY COMPUTER remove it later
		#self.ser.port = '/dev/tty6'
	# Open a file
	# send a packet ()
	def openFile(self, fileName):
		self.curFile = open(fileName, "rb")
		self.curContent = self.curFile.read()
	
	# this function handles the timing and resending stuff needed
	def sendRawPacket(self):
		self.send_int(self.fileOffset)
		self.send_int(self.packetNumber)
		self.send_int(self.curPacketSize)
		#self.endIndex
		self.send_int(self.curCRC) 
		self.ser.write(self.packet_data) 
		 
	def sendPacket(self):
		# send raw packet, repeat if nesceasry
		max = (self.send_packet_timeout/self.listen_timeout)
		for i in range [0, max]:
			self.sendRawPacket()
			found, val = self.listen()
			if(found):
				if (val == TRANSMIT_RECEIVED)
					# The packet was sent and the correct ack was received
					return True
			# if the wrong command is received or nothing is received things just continue
		# If the correct value is never found, the packet send failed
		return False
		
	def makePacket(self, offset, size):
		#
		end = offset+size
		packetContent = self.curContent[offset:end:1]
		packet_crc = binascii.crc32(packetContent,0)
		curPacketNumber = self.packetNumber + 1
		# It looks like this would be converted into 
		#print("makePacket is empty right now")
	
	def transmitFile(self, packet):
		while(self.file_packets_remaining == True):
			if(self.sendCommand(TRANSMIT, TRANSMIT_RECEIVED) ==False):
				#Transmit Failed because the command wasn't received
				return False
			if (self.sendPacket==False):
				#
				# Packet could not be Transmitted after several tries
				return False
			self.incrementPacketData()
		return True
	
	def rec_int(self):
		# this works and is complete
		self.ser.timeout = READ_TIMEOUT
		raw = self.ser.read(4)
		#raw = b'1299'
		#b = 1129
		#raw = b.to_bytes(4, 'little')
		clean = int.from_bytes(raw, 'little')
		return clean
	def send_int(self, number):
		int_form = number.to_bytes(4, byteorder='big', signed =False)
		self.send(int_form)
	def reset_timer(self, wait_time):
		system_time = time.time()*1000
		self.expire_time = system_time + self.expire_time
	def timer_not_expired(self):
		cur_time = time.time()*1000
		if cur_time< self.expire_time:
			return True
		else:
			return False
	def listen(self, max_time):
		self.reset_timer(max_time)
		#self.ser.timeout = max_time/1000
		self.ser.timeout = 0
		#cur_values = self.ser
		#
		cur_time = time.time()*1000

		while((time.time()*1000) <(cur_time+max_time) ):
			if(self.ser.in_waiting>0 ):
				#cur_values = self.ser.read(self.ser.in_waiting)
				#last_byte_sent = cur_values[-1]
				last_byte_sent = self.ser.read(1)
				return True, last_byte_sent
		return False, b'~'
	def send(self,to_send):
		self.ser.reset_output_buffer()
		self.ser.write(to_send)
	
	def send_listen(self, to_send, target_value, time_out):
		self.send(to_send)
		listen_found = self.listen(time_out)
		if(target_value == listen_found):
			return True, listen_found
		else:
			return False, listen_found
	def ping(self):
		self.ser.reset_input_buffer()
		self.ser.reset_output_buffer()

		self.send(b'P')
		was_found, return_val = self.listen(3000)
		if(was_found):
		#if (return_val == b'p'):
			return True, return_val
		else:
			# You can send the value found here if desired
			return False, b'~'
	def open_esp_file(self, remote_filename):
		self.ser.reset_input_buffer()
		self.ser.reset_output_buffer()
		self.send(b'O')
		was_found, ack = self.listen(3000)

		self.listen_timeout = 1000
		#found, ack = self.listen(self.listen_timeout)
		if(ack == b'o'):
			print("positive ack in open")
		else:
			print("Not a positivie ack in oper. esp returned : " + ack.decode('ascii'))
		remote_filename = remote_filename + "\n"
		#time.sleep(10)
		self.ser.write(remote_filename.encode('ascii'))
		found, ack =self.listen(self.listen_timeout)
		correct_return =False
		if(ack ==b'!'):
			correct_return = True
		else:
			correct_return = False
		return correct_return, ack
	def close_and_exit(self):
		# add code to catch a failed exit?? Could be caused by closed port
		self.ser.close()
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
	def five_part_init(self):
		self.ser.reset_input_buffer()
		self.ser.reset_output_buffer()
		cur_time =time.time() * 1000
		state = 0
		while((time.time()*1000 -cur_time ) <(self.init_connection_timeout*1000)):
			found_content, value = self.listen(self.wait_loop_timeout *1000)
			
			if(found_content):
				cur_time =time.time() * 1000
				
				if(state==0):
					if(value == b'a'):
						print("IN initial listen")
						self.send(b'b')
						state = 1
					 
				elif(state==1):
					print("state 1: " + value.decode('ascii') )

					if(value == b'c'):
						print("State 1")
						self.send(b'd')
						state =2
					else:
						state = 0
				elif(state ==2):
					if(value == b'e'):
						print("State 2")
						state = 3 # technically this isn't used rn, but state 3 would be "Connection Complete"
						return True
					else:
						state = 0
		return False


	def init_esp_connection(self):
		print("Listening for esp")
		self.ser.read_all
		self.ser.reset_input_buffer
		self.ser.reset_output_buffer
		state = 0
		last_val =b'~'
		count = 0 
		"""
		cur_time =time.time() * 1000


		while((time.time() +self.init_connection_timeout) >(cur_time)):
			found_content, value = self.listen(self.wait_loop_timeout *1000)
			if(found_content):
				cur_time =time.time() * 1000
				if(state==0):
					if(value == b'a'):
					self.send(b'b');
					state = 1 ; 
				elif(state==1):
					if(value == b'c'):
						self.send(b'd')
						state =2
				elif(state ==2):
					if(value == b'd'):
						state = 3 # technically this isn't used rn, but state 3 would be "Connection Complete"
						return True
			time.sleep(.001)


			

		"""
		while(True):
			time.sleep(.001)
			count = count +1
			if (self.ser.in_waiting>0):
				#print("Input Detected:")
				signal =self.ser.read(1)
				#self.ser.reset_input_buffer
				#$print(signal)
				if signal == b'a':
					self.ser.write(b'b')
					print("Caught a signal from esp. COunt: ")
					print(count)
					state = 1
					last_val = signal
					
				elif signal ==b'c':
					# write d final confirmation?
					#print("Sending Final acknowledgement, connection established")
					#return
					#print("C found")
					#print("Last val was: ")
					#print(last_val)
					print("C found: Count was: ")
					print(count)
					if state ==1:
						print("Probable handshake")
						return
				else:
					if (state ==1):
						print("Signal State: " + signal.decode('ascii') )
						print(signal)
					state = 0
					last_val = signal				

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


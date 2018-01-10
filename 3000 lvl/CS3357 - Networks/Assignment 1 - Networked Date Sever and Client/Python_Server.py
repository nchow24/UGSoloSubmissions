#Nicole Chow	nchow24 (250725575)
#Oct 20, 2017
#Server side

import socket
import datetime

TCP_IP = '192.168.243.128'
TCP_PORT = 5005

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)

while True: 
	conn, addr = s.accept()
	print('Server Address:', TCP_IP)
	print('Client Address:', addr)
	print("Connection to Client Established")

	# get client's input string
	input = conn.recv(1024).decode("ascii")
	print("Reading input: " + input + " from client...")
	response = ""

	# generate date if client asks for it, else generate a "no response" 
	if input == "What is the current date and time?":
		date = datetime.datetime.now()
		response = "Current Date and Time - " + str(date.month) + "/" +  str(date.day) + "/" + str(date.year) + " " + str(date.hour) + ":" + str(date.minute) + ":" + str(date.second)

	else:
		response = "Error - no response for the request"

	# send response back to client
	print("Sending appropriate response...")
	conn.send(response.encode())

	# stay open for next connection
	print("Waiting for next connection...")

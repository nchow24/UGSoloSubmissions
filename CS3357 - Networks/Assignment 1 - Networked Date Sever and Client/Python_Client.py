#Nicole Chow    nchow24 (250725575)
#Oct 20, 2017
#Client side

import socket

TCP_IP = '192.168.243.128'
TCP_PORT = 5005

print ("Attempting to contact server at ",TCP_IP,":",TCP_PORT)
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))
print ("Connection to Server Established")

# get input from user and send to server
userInput = input("Enter request please: ")
print("Sending your input to server...")
s.send(userInput.encode())

# get response from server and display it 
print("Receiving response from server...")
response = s.recv(1024).decode("ascii")
print(response)

s.close()

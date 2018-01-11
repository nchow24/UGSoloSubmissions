#Nicole Chow    nchow24 (250725575)
#Dec 1, 2017
#Server side


import binascii
import socket
import struct
import sys
import hashlib

#
#function creates and sends an ACK back to client (takes the sequence and client address as parameters)
#
def sendPacket(seq, addr):
    #Create the Checksum
    values = (1,seq,b'')
    UDP_Data = struct.Struct('I I 8s')
    packed_data = UDP_Data.pack(*values)
    chksum =  bytes(hashlib.md5(packed_data).hexdigest(), encoding="UTF-8")

    #Build the UDP Packet
    values = (1,seq,b'',chksum)
    UDP_Packet_Data = struct.Struct('I I 8s 32s')
    UDP_Packet = UDP_Packet_Data.pack(*values)

    #Send the UDP ACK packet back to client
    packet = unpacker.unpack(UDP_Packet)
    print("Sent packet:", packet)
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.sendto(UDP_Packet, addr)


#
#main
#
UDP_IP = "127.0.0.1"
UDP_PORT = 5005
unpacker = struct.Struct('I I 8s 32s')


#Create the socket and listen
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

seq = 0  #sequence of the ACK packet to be sent
seqGood = 1 #indicates if received packet is in order
checkSumGood = 1 #indicates of the chksum is good 

while True:
    #Receive Data
    data, addr = sock.recvfrom(1024)
    UDP_Packet = unpacker.unpack(data)
    print("Received packet from:", addr)
    print("Received message:", UDP_Packet)

    #Create the Checksum for comparison
    values = (UDP_Packet[0],UDP_Packet[1],UDP_Packet[2])
    packer = struct.Struct('I I 8s')
    packed_data = packer.pack(*values)
    chksum =  bytes(hashlib.md5(packed_data).hexdigest(), encoding="UTF-8")
    #Compare Checksums to test for corrupt data
    if UDP_Packet[3] == chksum:
        print('CheckSums Match, Packet OK')
        checkSumGood = 1
    else:
        print('Checksums Do Not Match, Packet Corrupt')
        checkSumGood = 0

    #check the seq number
    if (UDP_Packet[1] == seq):
        print('Sequence is correct, Packet in order')
        seqGood = 1
    else:
        print('Sequence is not correct, Packet not in order')
        seqGood = 0

    # Send ACK for this packet (packet sucessfuly received)
    # move forward to wait for the next packet (by changing seq)
    if (seqGood and checkSumGood):
        print('Packet (seq' + str(seq) + ') sucessfully received, sending ACK ' + str(seq) + ' back')
        sendPacket(seq, addr)
        if (seq == 1):
            seq = 0
        else:
            seq = 1
    # Send ACK for last packet (packet unsucessfully received)
    # stay in same state to wait for same seq number (by keeping seq the same)
    else:
        if (seq == 0):
            print('Packet (seq ' + str(seq) + ') unsucessfully received, sending ACK 1 back')
            sendPacket(1, addr)
        else:
            print('Packet (seq' + str(seq) + ') unsucessfully received, sending ACK 0 back')
            sendPacket(0, addr)
    print('')

# Nicole Chow    nchow24 (250725575)
# Dec 1, 2017
# Client side

import binascii
import socket
import struct
import sys
import hashlib
import signal
import time

#
# function creates and sends a packet to server (takes the sequence number and message as parameters)
#
def sendPacket(seq, message):
    # Create the Checksum
    values = (0, seq, message)
    UDP_Data = struct.Struct('I I 8s')
    packed_data = UDP_Data.pack(*values)
    chksum = bytes(hashlib.md5(packed_data).hexdigest(), encoding='UTF-8')

    # Build the UDP Packet
    values = (0, seq, message, chksum)
    UDP_Packet_Data = struct.Struct('I I 8s 32s')
    UDP_Packet = UDP_Packet_Data.pack(*values)

    # Send the UDP Packet
    packet = unpacker.unpack(UDP_Packet)
    print("Sent packet:", packet)
    sock.sendto(UDP_Packet, (UDP_IP, UDP_PORT))

    # timer start for 9ms
    signal.setitimer(signal.ITIMER_REAL, 0)
    signal.setitimer(signal.ITIMER_REAL, 0.009, 0)

#
# function raises a signal when timeout occurs
#
def signal_handler(signum, frame):
    global init
    raise Exception('Timed out!')


#
# main
#
UDP_IP = '127.0.0.1'
UDP_PORT = 5005
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
unpacker = struct.Struct('I I 8s 32s')

checkSumGood = 0  # used to check if the ACK packet is corrupt
seqGood = 0  # used to check if the ACK is for the last sent packet

print ('UDP target IP:', UDP_IP)
print ('UDP target port:', UDP_PORT)
print ('')

signal.signal(signal.SIGALRM, signal_handler)

# send 3 packets
for x in range(0, 3):
    # create the sequence number and message
    seq = 0
    message = ''
    if x == 0:
        seq = 0
        message = 'NCC-1701'.encode()
    elif x == 1:
        seq = 1
        message = 'NCC-1664'.encode()
    else:
        seq = 0
        message = 'NCC-1017'.encode()

    # send packet
    print ('Sending Packet ' + str(x + 1) + '(seq' + str(seq) + ')...')
    sendPacket(seq, message)

    # keep sending current packet until proper ACK is received
    while checkSumGood == 0 or seqGood == 0:
        
        # wait for/process an ACK unless timeout is reached
        try:
            # loop until a proper ACK is received
            while checkSumGood == 0 or seqGood == 0:
                # get ACK from sender
                (data, addr) = sock.recvfrom(1024)
                UDP_Packet = unpacker.unpack(data)
                print ('Received ACK packet from:', addr)
                print ('Received message:', UDP_Packet)
                
                # Create the Checksum for comparison
                values = (UDP_Packet[0], UDP_Packet[1], UDP_Packet[2])
                packer = struct.Struct('I I 8s')
                packed_data = packer.pack(*values)
                chksum = bytes(hashlib.md5(packed_data).hexdigest(), encoding='UTF-8')
                
                # Compare Checksums to test for corrupt data
                if UDP_Packet[3] == chksum:
                    print ('CheckSums Match, Packet OK')
                    checkSumGood = 1
                else:
                    print ('Checksums Do Not Match, Packet Corrupt')
                    checkSumGood = 0
                    
                # check if the ACK is for the last sent packet
                if UDP_Packet[1] == seq:
                    print ('Correct ACK received, no error in sending Packet')
                    seqGood = 1
                else:
                    print ('Incorrect ACK received, error in sending Packet')
                    seqGood = 0
                    
                # if packet not sent correctly, loop again to wait for the next ACK
                if checkSumGood == 0 or seqGood == 0:
                    print ('Corrupted packet received or packet not received by server')
                    print ('Waiting for correct ACK...')
                else:
                    print ('Packet sent correctly')
                    # stop timer
                    signal.setitimer(signal.ITIMER_REAL, 0)
                    print ('')
        # timeout
        except Exception:
            print ('Timeout! Resending packet')
            sendPacket(seq, message)

    # reset flags for the next packet
    checkSumGood = 0
    seqGood = 0
    print ('')

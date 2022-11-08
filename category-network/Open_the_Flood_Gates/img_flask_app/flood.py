#!/usr/bin/python3

import socket
import time
import random
from scapy.all import *
from scapy.layers.http import *
import os

MAX_SECONDS_TO_RUN  = 60 # 1 minute
MAX_PACKETS_TO_SEND = 5000

packetsSent = 0

dstIPAddr = os.environ['REMOTE_HOST']
srcIPAddr = socket.gethostbyname(socket.gethostname())

def sendICMPEcho():
   ip = IP(src = srcIPAddr, dst = dstIPAddr)
   icmp = ICMP()
   packet = ip/icmp/"THIS IS FROM flood.py"
   send(packet)
   global packetsSent
   packetsSent += 1

def sendDNSRequest():
   ip = IP(src = srcIPAddr, dst = dstIPAddr)
   udp = fuzz(UDP(dport = 53))
   dns = fuzz(DNS(qd = DNSQR(qname="seedsecuritylabs.org", qtype = "A")))
   packet = ip/udp/dns
   send(packet)
   global packetsSent
   packetsSent += 1

def sendHTTPResponse():
   ip = IP(src = srcIPAddr, dst = dstIPAddr)
   #udp = UDP()
   #http = HTTP()/HTTPResponse()
   tcp = TCP()
   http = "HTTP/1.1 200 OK \n THIS IS A TEST"
   #packet = ip/udp/http
   packet = ip/tcp/http
   send(packet)
   global packetsSent
   packetsSent += 1

random.seed()

totalSeconds = random.randint(1, MAX_SECONDS_TO_RUN)
totalPackets = random.randint(1, MAX_PACKETS_TO_SEND)

packetsPerSecond = totalPackets/totalSeconds

endTime = time.time() + totalSeconds

while time.time() < endTime and packetsSent < totalPackets:
   sendICMPEcho()
   sendDNSRequest()
   sendHTTPResponse()
   time.sleep(1/packetsPerSecond)

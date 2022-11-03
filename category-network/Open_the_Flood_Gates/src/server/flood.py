#!/usr/bin/python3

import socket
import time
import random
from scapy.all import *
from scapy.layers.http import *

MAX_SECONDS_TO_RUN  = 60 # 1 minute
MAX_PACKETS_TO_SEND = 5000

packetsSent = 0

if len(sys.argv) != 2:
   exit("Specify dest IP addr")

dstIPAddr = sys.argv[1]
srcIPAddr = socket.gethostbyname(socket.gethostname())

def sendICMPEcho():
   ip = IP(src = srcIPAddr, dst = dstIPAddr)
   icmp = ICMP()
   packet = ip/icmp
   send(packet)
   global packetsSent
   packetsSent += 1

def sendDNSRequest():
   ip = IP(src = srcIPAddr, dst = dstIPAddr)
   udp = UDP(sport = random.randint(10000, 60000), dport = 53)
   dns = DNS(qd = DNSQR(qname="seedsecuritylabs.org", qtype = "A"))
   packet = ip/udp/dns
   send(packet)
   global packetsSent
   packetsSent += 1

def sendHTTPResponse():
   ip = IP(src = srcIPAddr, dst = dstIPAddr)
   udp = UDP(sport = random.randint(10000, 60000), dport = random.randint(10000, 60000))
   http = HTTP()/HTTPResponse()
   packet = ip/udp/http
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

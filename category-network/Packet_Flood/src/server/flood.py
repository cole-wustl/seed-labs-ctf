#!/usr/bin/python3

import socket
import time
import random
from scapy.all import *

if len(sys.argv) != 2:
   exit("Specify dest IP addr")

dstIPAddr = sys.argv[1]
srcIPAddr = socket.gethostbyname(socket.gethostname())

def sendICMPEcho():
   packet = IP(src = srcIPAddr, dst = dstIPAddr)/ICMP()
   send(packet)

startTime = time.time()
endTime = startTime + 3 # run for 30 seconds

while time.time() < endTime:
   sendICMPEcho()

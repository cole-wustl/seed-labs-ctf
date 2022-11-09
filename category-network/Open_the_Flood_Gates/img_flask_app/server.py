#!/usr/local/bin/python3

from flask import *
from scapy.all import *
import time
import random
import socket

srcIPAddr = socket.gethostbyname(socket.gethostname())

def sendICMPEcho(srcIP, dstIP):
   #ip = IP(src = srcIP, dst = dstIP)
   ip = IP(src = "10.0.0.2", dst = dstIP)
   icmp = ICMP()
   packet = ip/icmp/"THIS IS FROM flood.py"
   send(packet)

application = Flask(__name__)

@application.route("/")
def landing_page():
   #srcIP = socket.gethostbyname(socket.gethostname())
   #dstIP = request.remote_addr
   #sendICMPEcho(srcIP, dstIP)
   #return "Sent ICMP Echo to " + str(request.remote_addr)
   return str(request.headers) + "\n" + str(request.host) + "\n" + str(request.remote_addr)
   #return str(request.remote_addr)
   #return send_file("/ctf/index.html")

if __name__ == "__main__":
   application.run("0.0.0.0")

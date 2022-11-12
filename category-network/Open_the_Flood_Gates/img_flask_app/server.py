#!/usr/local/bin/python3

from flask import *
from scapy.all import *
from werkzeug.middleware.proxy_fix import ProxyFix
from faker import Faker
import random
import os
import threading

MAX_PACKETS_TO_SEND = 1000

flag = os.environ['CTF_FLAG']

application = Flask(__name__)

application.wsgi_app = ProxyFix(application.wsgi_app, x_for=1, x_proto=1, x_host=1, x_prefix=1) # https://flask.palletsprojects.com/en/2.2.x/deploying/proxy_fix/

fake = Faker()

def craft_icmp_reply(dstIP):
   ip = IP(src = fake.ipv4_public(), dst = dstIP)
   icmp = ICMP(type = 0) # Echo reply
   packet = ip/icmp
   return packet

def craft_dns_request(dstIP):
   ip = IP(src = fake.ipv4_public(), dst = dstIP)
   udp = UDP(dport = 53)
   dns = DNS(qd = DNSQR(qname = fake.domain_name(), qtype = "A"))
   packet = ip/udp/dns
   return packet

def flood_packets(dstIP):
   random.seed()
   packetWithFlag = random.randint(0, MAX_PACKETS_TO_SEND - 1)
   
   for i in range(MAX_PACKETS_TO_SEND):
      packetToSend = random.choice(("ICMP", "DNS"))
      
      if packetToSend == "ICMP":
         packetToSend = craft_icmp_reply(dstIP)
      elif packetToSend == "DNS":
         packetToSend = craft_dns_request(dstIP)
       
      if i == packetWithFlag:
         packetToSend = packetToSend/flag 

      send(packetToSend)

@application.route("/")
def landing_page():
   dstIP = request.headers["X-Forwarded-For"]
   #send_icmp_reply(dstIP)
   #send_dns_request(dstIP)
   theThread = threading.Thread(target = flood_packets, args = (dstIP,))
   theThread.start()
   #flood_packets(dstIP)
   return send_file("/ctf/index.html")

if __name__ == "__main__":
   application.run("0.0.0.0")

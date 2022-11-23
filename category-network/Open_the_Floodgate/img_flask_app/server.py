#!/usr/local/bin/python3

from flask import *
from scapy.all import *
from scapy.layers.http import *
from werkzeug.middleware.proxy_fix import ProxyFix
from faker import Faker
import random
import os
import threading

flag = os.environ['CTF_FLAG']

application = Flask(__name__)

application.wsgi_app = ProxyFix(application.wsgi_app, x_for=1, x_proto=1, x_host=1, x_prefix=1) # https://flask.palletsprojects.com/en/2.2.x/deploying/proxy_fix/

fake = Faker()

def craft_http_reply(dstIP):
   ip = IP(src = "0.0.0.0", dst = dstIP)
   udp = UDP(sport = 80, dport = 80)
   http = HTTP()/HTTPResponse()
   packet = ip/udp/http
   return packet

def flood_http(dstIP):
   MAX_HTTP_PACKETS = 250
   random.seed()
   packetWithFlag = random.randint(0, MAX_HTTP_PACKETS - 1)
   for i in range(MAX_HTTP_PACKETS):
      packet = craft_http_reply(dstIP)
      if i == packetWithFlag:
         packet = packet/(" " + flag + " ")
      else:
         packet = packet/(" FOLLOW ME! ")
      send(packet)

def craft_icmp_reply(dstIP):
   ip = IP(src = "0.0.0.0", dst = dstIP)
   icmp = ICMP(type = 0) # Echo reply
   packet = ip/icmp
   return packet

def flood_icmp(dstIP):
   MAX_ICMP_PACKETS = 1000
   random.seed()
   packetWithHint = random.randint(0, MAX_ICMP_PACKETS - 1)
   for i in range(MAX_ICMP_PACKETS):
      packet = craft_icmp_reply(dstIP)
      if i == packetWithHint:
         packet = packet/("VISIT /sniff")
      else:
         packet = packet/(('\0' * 64) + "ARE YOU LISTENING?")
      send(packet)

def craft_dns_reply(dstIP):
   ip = IP(src = "0.0.0.0", dst = dstIP)
   udp = UDP(dport = 53)
   dns = DNS(qr = 1, qd = DNSQR(qname = fake.ipv4_private(), qtype = "A")) # qr = 1 means reply
   packet = ip/udp/dns
   return packet

def flood_dns(dstIP):
   MAX_DNS_PACKETS = 500
   random.seed()
   packetWithHint = random.randint(0, MAX_DNS_PACKETS - 1)
   for i in range(MAX_DNS_PACKETS):
      packet = craft_dns_reply(dstIP)
      if i == packetWithHint:
         packet = packet/("NAVIGATE TO /capture")
      else:
         packet = packet/(('0' * random.randint(0, 100)) + "ARE YOU ANALYZING?")
      send(packet)

@application.route("/")
def root_page():
   dstIP = request.headers["X-Forwarded-For"]
   theThread = threading.Thread(target = flood_icmp, args = (dstIP,))
   theThread.start()
   return "<h1><center><a href='https://en.wikipedia.org/wiki/Packet_analyzer' target='_blank'>Packet Analyzer</a></center></h1>"

@application.route("/sniff")
def sniff():
   dstIP = request.headers["X-Forwarded-For"]
   theThread = threading.Thread(target = flood_dns, args = (dstIP,))
   theThread.start()
   return "<h1><center><a href='https://datatracker.ietf.org/doc/html/rfc1035' target='_blank'>RFC 1035</a></center></h1>"

@application.route("/capture")
def capture():
   dstIP = request.headers["X-Forwarded-For"]
   theThread = threading.Thread(target = flood_http, args = (dstIP,))
   theThread.start()
   return "<h1><center><a href='https://en.wikipedia.org/wiki/User_Datagram_Protocol#Comparison_of_UDP_and_TCP' target='_blank'>UDP vs. TCP</a></center></h1>"

@application.route("/flag")
def fake_flag():
   return f"<h1><center>The flag is: {fake.binary(length = random.randint(15, 50)).decode('ascii', 'ignore')}</center></h1>"

@application.route("/<path:page>")
def generic_page(page):
   return f"<h1><center>Welcome to {page}</center></h1>"

if __name__ == "__main__":
   application.run("0.0.0.0")


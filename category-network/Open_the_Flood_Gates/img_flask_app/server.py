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

def craft_icmp_request(dstIP):
   ip = IP(src = fake.ipv4_public(), dst = dstIP)
   icmp = ICMP(type = 8) # Echo request
   packet = ip/icmp
   return packet

def craft_dns_request(dstIP):
   ip = IP(src = fake.ipv4_public(), dst = dstIP)
   udp = UDP(dport = 53)
   dns = DNS(qd = DNSQR(qname = fake.domain_name(), qtype = "A"))
   packet = ip/udp/dns
   return packet

def craft_tcp_syn(dstIP):
   ip = IP(src = fake.ipv4_public(), dst = dstIP)
   tcp = TCP(flags = 'S') # TCP SYN
   packet = ip/tcp
   return packet

def flood_packets(dstIP):
   random.seed()
   packetWithFlag = random.randint(0, MAX_PACKETS_TO_SEND - 1)

   for i in range(MAX_PACKETS_TO_SEND):
      packetToSend = random.choice(("ICMP", "DNS", "TCP"))

      if packetToSend == "ICMP":
         packetToSend = craft_icmp_request(dstIP)
      elif packetToSend == "DNS":
         packetToSend = craft_dns_request(dstIP)
      elif packetToSend == "TCP":
         packetToSend = craft_tcp_syn(dstIP)

      if i == packetWithFlag:
         packetToSend = packetToSend/flag

      send(packetToSend)

def flood_icmp_echo_request(dstIP):
   MAX_ICMP_PACKETS = 1000
   random.seed()
   packetWithHint = random.randint(0, MAX_ICMP_PACKETS - 1)
   for i in range(MAX_ICMP_PACKETS):
      packet = craft_icmp_request(dstIP)
      if i == packetWithHint:
         packet = packet/("VISIT /sniff")
      else:
         packet = packet/(fake.binary(length = 64))
         #packet = packet/(fake.sentence(nb_words = 10))
      send(packet)

@application.route("/")
def index():
   dstIP = request.headers["X-Forwarded-For"]
   theThread = threading.Thread(target = flood_icmp_echo_request, args = (dstIP,))
   theThread.start()
   return send_file("/ctf/index.html")

@application.route("/flag")
def fake_flag():
   return f"<h1> The flag is: {fake.word()} </h1>"

@application.route("/<page>")
def generic_page(page):
   return f"<h1> Welcome to {page} </h1>\n<p> {fake.paragraph(nb_sentences = 10)} </p>"

if __name__ == "__main__":
   application.run("0.0.0.0")


#!/usr/local/bin/python3

from flask import *
from scapy.all import *
from werkzeug.middleware.proxy_fix import ProxyFix
import time
import random
import socket


#srcIPAddr = socket.gethostbyname(socket.gethostname())

def sendICMPEcho(srcIP, dstIP):
   ip = IP(src = srcIP, dst = dstIP)
   icmp = ICMP()
   packet = ip/icmp/"THIS IS FROM flood.py"
   send(packet)

application = Flask(__name__)

application.wsgi_app = ProxyFix(application.wsgi_app, x_for=1, x_proto=1, x_host=1, x_prefix=1) # https://flask.palletsprojects.com/en/2.2.x/deploying/proxy_fix/

@application.route("/")
def landing_page():
   srcIP = socket.gethostbyname(socket.gethostname())
   dstIP = request.headers["X-Real-Ip"]
   sendICMPEcho(srcIP, dstIP)
   #return "Sent ICMP Echo to " + str(request.remote_addr)
   #return str(request.headers) + str(request.host) + str(request.remote_addr)
   #return str(request.remote_addr)
   return send_file("/ctf/index.html")
   #return str(request.headers["X-Real-Ip"])

if __name__ == "__main__":
   application.run("0.0.0.0")

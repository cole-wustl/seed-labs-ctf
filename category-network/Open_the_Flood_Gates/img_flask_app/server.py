#!/usr/local/bin/python3

from flask import *
from scapy.all import *
from werkzeug.middleware.proxy_fix import ProxyFix
from faker import Faker
import time
import random

application = Flask(__name__)

application.wsgi_app = ProxyFix(application.wsgi_app, x_for=1, x_proto=1, x_host=1, x_prefix=1) # https://flask.palletsprojects.com/en/2.2.x/deploying/proxy_fix/

fake = Faker()

def send_icmp_reply(dstIP):
   srcIP = fake.ipv4()
   ip = IP(src = srcIP, dst = dstIP)
   icmp = ICMP(type = 0) # Echo reply
   packet = ip/icmp/"THIS IS FROM flood.py"
   send(packet)


@application.route("/")
def landing_page():
   dstIP = request.headers["X-Forwarded-For"]
   send_icmp_reply(dstIP)
   return send_file("/ctf/index.html")

if __name__ == "__main__":
   application.run("0.0.0.0")

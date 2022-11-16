FROM python:3-alpine

LABEL Author="Dylan Simmons <dylan.simmons@wustl.edu>"

#ARG PACKAGES="libpcap"
#RUN apk add --no-cache ${PACKAGES}

COPY requirements.txt /ctf/requirements.txt
RUN pip3 install --upgrade pip
RUN pip3 install -r /ctf/requirements.txt

COPY server.py /ctf/server.py
RUN chmod 0755 /ctf/server.py

COPY packet_analyzer.html /ctf/packet_analyzer.html
COPY internet_protocol.html /ctf/internet_protocol.html
COPY transmission_control_protocol.html /ctf/transmission_control_protocol.html

COPY health.sh /ctf/health.sh
RUN chmod 0755 /ctf/health.sh
HEALTHCHECK --interval=60s --timeout=10s --start-period=30s --retries=1 CMD /ctf/health.sh

EXPOSE 8000
EXPOSE 8225

COPY entry.sh /ctf/entry.sh
RUN chmod 0755 /ctf/entry.sh
ENTRYPOINT ["/ctf/entry.sh"]

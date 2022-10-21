# Use Ubuntu v20.04 since that's what's used in the SEED Lab
FROM ubuntu:20.04

# Default arg values, most will be overwritten in docker-compose.yml
ARG PACKAGES="xinetd netcat"

# Docker documentation reccomends executing apt-get update and apt-get install in the same RUN command
RUN apt-get update && apt-get install -y ${PACKAGES} && rm -rf /var/lib/apt/lists/*

COPY xinetd.conf /etc/xinetd.conf
COPY banner_success /ctf/banner_success
COPY banner_fail /ctf/banner_fail
COPY entry.sh /ctf/entry.sh
COPY flag.txt /root/flag.txt
COPY health.sh /ctf/health.sh
COPY simpleShell.sh /ctf/simpleShell.sh

RUN chmod 0700 /ctf/entry.sh
RUN chmod 0700 /ctf/health.sh
RUN chmod 0700 /ctf/simpleShell.sh

EXPOSE 49575/tcp

HEALTHCHECK CMD /ctf/health.sh

ENTRYPOINT ["/ctf/entry.sh"]


# Use Ubuntu v20.04 since that's what's used in the SEED Lab
FROM ubuntu:20.04

# Default arg values, most will be overwritten in docker-compose.yml
ARG PACKAGES="xinetd netcat"

# Docker documentation reccomends executing apt-get update and apt-get install in the same RUN command
RUN apt-get update && apt-get install -y ${PACKAGES} && rm -rf /var/lib/apt/lists/*

# Add new user account.
RUN useradd --home-dir /home/seed --create-home --uid 1000 --shell /usr/bin/bash seed

COPY banner_success /ctf/
COPY banner_fail    /ctf/
COPY entry.sh       /ctf/
COPY health.sh      /ctf/
COPY server.sh      /ctf/
COPY xinetd.conf    /etc/
COPY flag.txt       /flag/

RUN chmod 0755 /ctf/*
RUN chmod 0644 /flag/flag.txt

EXPOSE 49575/tcp

HEALTHCHECK CMD /ctf/health.sh

ENTRYPOINT ["/ctf/entry.sh"]


FROM nginx:latest

LABEL Author="Dylan Simmons <dylan.simmons@wustl.edu>"

ARG PACKAGES="netcat"

RUN apt-get update && apt-get install -y "${PACKAGES}" && rm -rf /var/lib/apt/lists/*

# Delete default config file
RUN rm /etc/nginx/conf.d/default.conf

COPY nginx.conf /etc/nginx/nginx.conf

COPY health.sh /ctf/health.sh
RUN chmod 0755 /ctf/health.sh
HEALTHCHECK --interval=60s --timeout=10s --start-period=30s --retries=1 CMD /ctf/health.sh

EXPOSE 3580

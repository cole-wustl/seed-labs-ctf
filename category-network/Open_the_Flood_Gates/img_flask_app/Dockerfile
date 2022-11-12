FROM python:3-alpine

LABEL Author="Dylan Simmons <dylan.simmons@wustl.edu>"

COPY requirements.txt /ctf/requirements.txt
RUN pip3 install --upgrade pip
RUN pip3 install -r /ctf/requirements.txt

COPY server.py /ctf/server.py
RUN chmod 0755 /ctf/server.py

COPY index.html /ctf/index.html

EXPOSE 8000

COPY entry.sh /ctf/entry.sh
RUN chmod 0755 /ctf/entry.sh
ENTRYPOINT ["/ctf/entry.sh"]

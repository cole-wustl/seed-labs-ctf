#!/bin/sh

gunicorn -b 0.0.0.0:8000 ctf.server

#flask --app /ctf/server.py --debug run --host=0.0.0.0

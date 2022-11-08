#!/bin/sh

#gunicorn --config=/ctf/gunicorn_conf.py app:app

flask --app /ctf/server.py --debug run --host=0.0.0.0

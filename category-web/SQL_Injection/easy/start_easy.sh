#!/bin/bash
docker-compose --file docker-compose_easy.yml up -d
docker ps --filter name=ctf_sqli_mysql_easy --filter name=ctf_sqli_web_easy

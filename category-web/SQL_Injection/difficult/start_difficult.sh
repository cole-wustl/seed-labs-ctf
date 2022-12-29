#!/bin/bash
docker-compose --file docker-compose_difficult.yml up -d
docker ps --filter name=ctf_sqli_mysql_diff --filter name=ctf_sqli_web_diff

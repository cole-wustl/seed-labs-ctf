#!/bin/bash
docker stop $(docker ps --filter name=ctf_sqli_mysql_diff --filter name=ctf_sqli_web_diff --quiet)

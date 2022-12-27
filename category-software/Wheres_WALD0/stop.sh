#!/bin/bash
docker stop $(docker ps --quiet --filter ancestor='wald0:latest')

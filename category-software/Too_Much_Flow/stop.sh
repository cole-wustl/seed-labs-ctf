#!/bin/bash
docker stop $(docker ps --quiet --filter ancestor=too-much-flow:latest)

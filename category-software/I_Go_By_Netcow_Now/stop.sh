#!/bin/bash
docker stop $(docker ps --quiet --filter ancestor="netcow:latest")

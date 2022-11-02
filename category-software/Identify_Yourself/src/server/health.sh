#!/bin/bash

PORT=49575

# See if port is open for TCP connection, 1 second timeout
nc -z -v -w 1 localhost "$PORT" &> /dev/null

CONN=$?

if [ "$CONN" != 0 ];
then
   exit 1 # fail
fi

exit 0 # success


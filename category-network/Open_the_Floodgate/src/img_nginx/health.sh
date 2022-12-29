#!/bin/sh

HEALTH_STATUS=0 # 0 = healthy, 1 = unhealthy

cp /dev/null /ctf/health.log # clear contents of /ctf/health.log

# Check if gunicorn port 8000 is open for TCP connection
nc -z localhost 8000 1> /dev/null 2>&1

if [ "$?" -eq 0 ];
then
   echo "Port 8000 is open." >> /ctf/health.log
else
   echo "Port 8000 is closed." >> /ctf/health.log
   HEALTH_STATUS=1
fi

# Check if HTML content can be fetched on port 3580
curl --silent --output /dev/null localhost:3580

if [ "$?" -eq 0 ];
then
   echo "Fetched HTML content on port 3580." >> /ctf/health.log
else
   echo "Failed to fetch HTML content on port 3580." >> /ctf/health.log
   HEALTH_STATUS=1
fi

if [ "$HEALTH_STATUS" -eq 0 ];
then
   echo "This container is healthy." >> /ctf/health.log
else
   echo "This container is unhealthy." >> /ctf/health.log
fi

exit $HEALTH_STATUS

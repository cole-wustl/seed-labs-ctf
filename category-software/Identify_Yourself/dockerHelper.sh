#!/bin/bash

printHelp() {
   echo
   echo "Usage: dockerHelper.sh <OPTION>"
   echo "Manage the Docker app for the Identify Yourself CTF."
   echo "If any of the Docker commands fail you may need to run with root priviliges."
   echo
   echo "Options:"
   echo "   -b   build the Docker image"
   echo "   -h   show this help dialogue"
   echo "   -k   stop the Docker app"
   echo "   -r   run the Docker app"
   echo "   -s   print the status of the Docker app"
   echo
}

buildImage()
{
   DOCKER_BUILD_OPTIONS="--no-cache --pull"
   docker-compose build $DOCKER_BUILD_OPTIONS
}

runApp()
{
   DOCKER_RUN_OPTIONS="--detach"
   docker-compose up "$DOCKER_RUN_OPTIONS"
}

stopApp()
{
   docker-compose down
}

dockerStatus()
{
   docker-compose ps
}

if [ "$#" -eq 0 ]; then
   printHelp
   exit 1
else
   while getopts 'bhkrs' OPTION; do
      case "$OPTION" in
         b) buildImage
            ;;
         h) printHelp
            ;;
         k) stopApp
            ;;
         r) runApp
            ;;
         s) dockerStatus
            ;;
         *) printHelp
            exit 1
            ;;
      esac
   done
   exit 0
fi


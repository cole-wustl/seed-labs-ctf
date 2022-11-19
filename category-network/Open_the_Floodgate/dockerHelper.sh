#!/bin/bash

printHelp() {
   echo
   echo "Usage: dockerHelper.sh <OPTIONS>"
   echo "Manage the Docker app for the 'Open the Floodgate' CTF."
   echo "If any of the Docker commands fail you may need to run with root priviliges."
   echo "Options can be combined and will be executed in the order supplied."
   echo
   echo "Options:"
   echo "   -h   Show this help dialogue."
   echo "   -k   Stop (kill) the Docker app."
   echo "   -r   Run the Docker app."
   echo "   -s   Print the status of the Docker app."
   echo
   echo "Examples:"
   echo "   ./dockerHelper.sh -k     Stop the Docker app."
   echo "   ./dockerHelper.sh -rs    Start the Docker app, then print the status."
   echo
}

runApp()
{
   DOCKER_RUN_OPTIONS="--build --detach"
   docker-compose up $DOCKER_RUN_OPTIONS
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
   while getopts 'hkrs' OPTION; do
      case "$OPTION" in
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


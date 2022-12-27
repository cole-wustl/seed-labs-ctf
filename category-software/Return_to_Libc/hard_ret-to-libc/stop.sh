#!/bin/bash

if [ -n "$(docker ps -f name=hard_ret-to-libc -q)" ]
then
   echo "STOPPING CONTAINERS..."
   echo
   docker stop $(docker ps -f name=hard_ret-to-libc -q)
   echo 
fi

if [ -z "$(docker ps --quiet --filter name=ret-to-libc)" ]
then
   echo "ENABLING ASLR..."
   echo
   sudo sysctl -w kernel.randomize_va_space=2
else
   echo
   echo "LEAVING ASLR DISABLED BECAUSE ANOTHER ret-to-libc CTF IS STILL RUNNING..."
   echo
fi

ASLR=$(cat /proc/sys/kernel/randomize_va_space)

if [ $ASLR -ne 2 ]
then
   echo
   echo "  █████   ███   █████   █████████   ███████████   ██████   █████ █████ ██████   █████   █████████  ███"
   echo " ░░███   ░███  ░░███   ███░░░░░███ ░░███░░░░░███ ░░██████ ░░███ ░░███ ░░██████ ░░███   ███░░░░░███░███"
   echo "  ░███   ░███   ░███  ░███    ░███  ░███    ░███  ░███░███ ░███  ░███  ░███░███ ░███  ███     ░░░ ░███"
   echo "  ░███   ░███   ░███  ░███████████  ░██████████   ░███░░███░███  ░███  ░███░░███░███ ░███         ░███"
   echo "  ░░███  █████  ███   ░███░░░░░███  ░███░░░░░███  ░███ ░░██████  ░███  ░███ ░░██████ ░███    █████░███"
   echo "   ░░░█████░█████░    ░███    ░███  ░███    ░███  ░███  ░░█████  ░███  ░███  ░░█████ ░░███  ░░███ ░░░ "
   echo "     ░░███ ░░███      █████   █████ █████   █████ █████  ░░█████ █████ █████  ░░█████ ░░█████████  ███"
   echo "      ░░░   ░░░      ░░░░░   ░░░░░ ░░░░░   ░░░░░ ░░░░░    ░░░░░ ░░░░░ ░░░░░    ░░░░░   ░░░░░░░░░  ░░░ "
   echo 
   echo "ADDRESS SPACE LAYOUT RANDOMIZATION (ASLR) IS DISABLED ON THE HOST."
   echo "THIS IS A SERIOUS SECURITY VULNERABILITY THAT WILL PERSIST BEYOND RUNNING THIS CHALLENGE!"
   echo 
   echo "ENABLE ASLR VIA 'sudo sysctl -w kernel.randomize_va_space=2'"
else
   echo
   echo "ASLR IS ENABLED, YOUR HOST SYSTEM IS SAFE AGAIN!"
fi


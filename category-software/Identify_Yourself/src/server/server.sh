#!/bin/bash

while :
do
   echo -n "$(whoami) $(pwd) $ " # Print command prompt
   read INPUT
   eval "$INPUT" 2> /dev/null
done


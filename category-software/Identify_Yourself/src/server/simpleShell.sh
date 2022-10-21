#!/bin/bash

while :
do
   echo -n "$ "
   read INPUT
   eval "$INPUT" 2> /dev/null
done


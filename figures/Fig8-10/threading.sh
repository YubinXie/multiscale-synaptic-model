#!/bin/sh

# Script to run processes in parallel from Manu N Setty
# Manu N Setty
# 11/15/2009

# INPUTS   The set of parameters to be looped over
# CMD      Command to be run
# NO_PROC  No of processes


INPUTS=()
CMD=./script.sh
NO_PROC=56
PID_ARRAY=()
IFS=$'\n'  
index=0
for file in `cat command.txt`
do
echo $file
INPUTS[$index]=$file
index=`expr $index + 1`
done

index=0
inlength=${#INPUTS[*]}
while [ $index != ${NO_PROC} ]
do
    PID_ARRAY[$index]=67128
    index=`expr $index + 1`
done


index=0
while [ $index != $inlength ]
do
    pidindex=0
    while [ $pidindex != $NO_PROC ]
    do
      running=`ps -p ${PID_ARRAY[${pidindex}]} | wc -l`
      if [ ${running} == 1 ] 
	  then
	      echo "Now running for inputs ${INPUTS[$index]}"
	          `$CMD ${INPUTS[$index]}` &
		      PID_ARRAY[${pidindex}]=$!
		          index=`expr $index + 1`
			  fi
      pidindex=`expr $pidindex + 1`
    done
    
    sleep 25
    
done
wait ${PID_ARRAY[*]}


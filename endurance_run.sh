#!/bin/sh

if [ $# -gt 0 ]; then
	max_iterations=$1
else
	max_iterations=1000
fi

iteration=0

while [ $iteration -lt $max_iterations ]; do
    command_to_run
    if [ $? -ne 0 ]; then
        break
    fi
    iteration=$((iteration+1))
done

#!/bin/sh

if [ $# -gt 0 ]; then
	max_iterations=$1
else
	max_iterations=1000
fi

iteration=0

while [ $iteration -lt $max_iterations ]; do
    ./generator --big-superposition | ./lem-in &> last.log
    if [ $? -ne 0 ]; then
		echo "crash on iteration $iteration"
        break
    fi
    iteration=$((iteration+1))
	echo "iteration $iteration pass"
done

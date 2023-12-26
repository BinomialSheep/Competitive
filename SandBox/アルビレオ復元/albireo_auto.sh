#!/bin/bash

for i in $(seq -w 0 10000)
do
	./albireo_rand_graph.out > input.txt
	./albireo_solver.out < input.txt > output.txt
	result=$(head -n 1 ./output.txt)
	echo "$result"
	if [ "$result" != "-1" ]; then
		echo "hoyo"
		break
	else
		echo ${i}	
	fi
done

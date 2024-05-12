#!/bin/bash

for d in $(seq 1 100)
do
	echo ${d}
	for n in $(seq  1 1000)
	do
		# echo ${d} ${n}
		echo ${d} ${n} | ./a.out > /dev/null
	done
done
for i in $(seq 1 100000)
do
	d=$((RANDOM % 100 + 1))
	n=$((RANDOM + 1))
	echo ${d} ${n}
	echo ${d} ${n} | ./a.out > /dev/null
done
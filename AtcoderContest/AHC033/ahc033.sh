#!/bin/sh

rm ../../debug.txt
for i in $(seq -w 0 99)
do
	# ../../a.out < in_1000_seed2/0${i}.txt > ../../output.txt 2>> ../../debug.txt
	../../a.out < in/00${i}.txt > out/00${i}.txt 2>> ../../debug.txt
	echo ${i}
done

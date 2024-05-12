#!/bin/sh

rm ../../debug.txt
for i in $(seq -w 0 99)
do
	../../a.out < in/00${i}.txt > ../../output.txt 2>> ../../debug.txt
	# echo ${i}
done

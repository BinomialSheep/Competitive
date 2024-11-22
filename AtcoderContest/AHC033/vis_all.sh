#!/bin/sh

for i in $(seq -w 0 99)
do
	echo ${i}
	../../a.out < in/00${i}.txt > out/00${i}.txt 2>> ../../debug.txt
	./vis.exe in/00${i}.txt out/00${i}.txt
done

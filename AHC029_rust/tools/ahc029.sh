#!/bin/bash

# for i in $(seq -w 0 999)
rm debug.txt
rm out.txt
rm score.txt
for i in $(seq -w 0 99)
do
	./target/release/tester ../../a.out < in/00${i}.txt > out.txt 2>> debug.txt
done
cat maxScore.txt debug.txt | ./sumScore.out > score.txt

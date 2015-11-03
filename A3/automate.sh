#!/bin/bash
rm outfile.txt

n=100
for((i=1; i<7; i++))
do
./P1A3 "$n" >>outfile.txt
let n=$n*10
done

let n=100

for((i=1; i<7; i++))
do
./P2A3 "$n" >>outfile.txt
let n=$n*10
done

cat outfile.txt
exit 0

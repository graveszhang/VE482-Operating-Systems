#!/bin/bash

file=text.txt

if ! [ -f $file ]
then
	echo 0 > $file
fi

for i in `seq 1 100`
do
	cnt=$(tail -1 $file)
	echo $((++cnt)) >> $file
done

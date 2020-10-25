#!/bin/sh
file=text.txt

if ! [ -f $file ]
then
	echo 0 > $file
fi

for i in `seq 1 100`
do
    exec 3<$file
    flock -x 3
	cnt=$(tail -1 $file)
	echo $((++cnt)) >> $file
    flock -u 3
    exec 3>&-
done

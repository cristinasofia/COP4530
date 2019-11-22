#!/bin/bash

tmp=$(tempfile)
echo "Your tempfile is named '$tmp' --- please make sure that it is deleted."

for program in ./bstsort ./heapsort ./triesort
do
    echo "Testing $program ..."
    for test in ../Tests/*
    do
	time $program < $test > $tmp && ./valsort $tmp
    done
done

rm $tmp

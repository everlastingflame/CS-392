#!/bin/bash
# addargs.sh

# Iterating over elements
ARGS=($@)
sum=0
echo ${ARGS[@]}
for elem in ${ARGS[@]}; do
   sum=$(( sum+elem ))
done
echo sum $sum


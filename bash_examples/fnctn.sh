#!/bin/bash
#fnctn.sh
height = 3

function volume {
 #vol is a local variable
 vol = $(($height * $1 * $2))
 echo $vol
}

volume 10 20 

result = $(volume 10 20)

echo "Result: $result"

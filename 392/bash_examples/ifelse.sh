#!/bin/bash
# ifelse.sh

CURR_PATH=$(pwd)
if [[ $CURR_PATH = ""/home/philippos" ]]; then
    echo "Yay!"
else
    echo "Nay!"
fi

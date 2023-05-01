#!/bin/bash

echo "Enter a port number for the server:"
read PORT

gcc -o server server.c
gcc -o client client.c

./server $PORT &

SERVER_PID=$(pidof server)

sleep 1
./client $PORT

pkill server

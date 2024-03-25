#!/bin/bash

LOG=data.log

BINARY=mandelbrot

echo "With -O0:">>$LOG
"Debug/$BINARY" -t 2>>$LOG
echo "With -Ofast -march=native:">>$LOG
"Release/$BINARY" -t 2>>$LOG

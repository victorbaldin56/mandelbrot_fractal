#!/bin/bash

mkdir -p ../logs
LOG=../logs/data.log

O0_DIR=../build/O0
O3_DIR=../build/O3
OFAST_DIR=../build/Ofast

BINARY=mandelbrot

$O0_DIR/$BINARY -t 2>>$LOG
$O3_DIR/$BINARY -t 2>>$LOG
$OFAST_DIR/$BINARY -t 2>>$LOG

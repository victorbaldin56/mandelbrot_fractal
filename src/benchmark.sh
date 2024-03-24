#!/bin/bash

O0_DIR=../build/O0
O3_DIR=../build/O3
OFAST_DIR=../build/Ofast

BINARY=mandelbrot

echo '-O0 output:'
$O0_DIR/$BINARY -t

echo '-O3 output:'
$O3_DIR/$BINARY -t

echo '-Ofast output:'
$OFAST_DIR/$BINARY -t

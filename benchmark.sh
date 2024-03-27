#!/bin/bash

CSV_DIR=logs/
DEBUG_BINARY=Debug/mandelbrot
RELEASE_BINARY=Release/mandelbrot
DEBUG_OUTPUT=no_optimization.csv
RELEASE_OUTPUT=with_optimization.csv

mkdir -p $CSV_DIR
cd Debug/
ninja
cd ../Release
ninja
cd ..

sudo cpupower frequency-set -g performance
$DEBUG_BINARY -t $CSV_DIR/$DEBUG_OUTPUT
$RELEASE_BINARY -t $CSV_DIR/$RELEASE_OUTPUT

python3 plot.py

#!/bin/bash

O0_DIR=./build/O0
O3_DIR=./build/O3
OFAST_DIR=./build/Ofast

mkdir -p $O0_DIR
mkdir -p $O3_DIR
mkdir -p $OFAST_DIR

cmake . -G Ninja -B $O0_DIR -D O0=1 -D O3=0 -D Ofast=0
cd $O0_DIR
ninja

cd ../../
cmake . -G Ninja -B $O3_DIR -D O3=1 -D O0=0 -D Ofast=0
cd $O3_DIR
ninja

cd ../../
cmake . -G Ninja -B $OFAST_DIR -D Ofast=1 -D O0=0 -D O3=0
cd $OFAST_DIR
ninja

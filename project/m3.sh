#!/usr/bin/bash
make
./m3 output m3-output A 3 10 0.515
./m3 output m3-output B 8 7 0.500
./m3 output m3-output C 3 11 0.495
./m3 output m3-output D 1 39 0.500
./m3_res m3-output output.txt > precision.txt 

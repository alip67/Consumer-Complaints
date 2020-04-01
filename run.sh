#!/bin/bash
#
# Use this shell script to compile (if necessary) your code and then execute it. 


cd src/
make
time ./application ../input/complaints.csv ../output/report.csv
cd ..


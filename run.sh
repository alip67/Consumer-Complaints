#!/bin/bash
#
# Use this shell script to compile (if necessary) your code and then execute it. 

chmod 755 run.sh
cd src/
make
time ./application ../input/complaints.csv ../output/generated_report.csv
cd ..


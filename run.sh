#!/bin/bash
#
# Use this shell script to compile (if necessary) your code and then execute it. 


cd src/
chmod 755 run.sh
time ./application ../insight_testsuit/test_1/input/complaints.csv ../insight_testsuit/test_1/output/generated_report.csv
cd ..


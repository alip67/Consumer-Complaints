#!/bin/bash
#
# Use this shell script to compile (if necessary) your code and then execute it. 

chmod 755 run.sh
cd src/

time ./application ../insight_testsuit/test_1/input/complaints.csv ../insight_testsuit/test_1/output/generated_report.csv
cd ..


#!/bin/bash

#shopt -s compat32
./tt.sh 'exit'
./tt.sh 'exit 0'
./tt.sh 'exit 1'
./tt.sh 'exit 2 1'
./tt.sh 'exit 127'
./tt.sh 'exit 128'
./tt.sh 'exit 255'
./tt.sh 'exit 256'
./tt.sh 'exit 257'
./tt.sh 'exit -2'
./tt.sh 'exit -222'
./tt.sh 'exit -127'
./tt.sh 'exit -128'
./tt.sh 'exit 2147483647'
./tt.sh 'exit 2147483648'
./tt.sh 'exit 9223372036854775807'
./tt.sh 'exit -2147483648'
./tt.sh 'exit -9223372036854775807'
./tt.sh 'exit -9223372036854775808'

# bash 3.2 exit status 255, bash 5 exit status 2:

# ./tt.sh 'exit a'
# ./tt.sh 'exit 92233720368547758070'
# ./tt.sh 'exit 92233720368547758079'
# ./tt.sh 'exit 9223372036854775808'
# ./tt.sh 'exit 92233720368547758080'
# ./tt.sh 'exit 11111111111111111111111111111111'
# ./tt.sh 'exit -92233720368547758070'
# ./tt.sh 'exit -92233720368547758079'
# ./tt.sh 'exit -92233720368547758080'
# ./tt.sh 'exit -92233720368547758089'
# ./tt.sh 'exit -1111111111111111111111111'

#!/bin/bash

make > /dev/null || exit 1
echo 'make: ok!'

cd tests
./1test_all.sh

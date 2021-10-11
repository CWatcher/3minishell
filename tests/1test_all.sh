#!/bin/bash



./tt.sh 'ls'
./tt.sh 'ls
ls
ls'
./tt.sh 'ls | wc > out.txt'
./tt.sh '<Makefile cat | wc >out.txt'
./tt.sh '< Makefile cat | wc > out.txt'
./tt.sh 'cat < Makefile | > out.txt wc '
./tt.sh 'ls < Makefile | cat < Makefile | > out.txt wc '
./tt.sh ' ls > out.txt | wc'
./tt.sh 'cat < Makefile | cat < Makefile > out.txt | > out.txt wc '
./tt.sh 'ls | wc'
ulimit -n 18
./tt.sh 'ls|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc'

./echo.sh
./exit.sh

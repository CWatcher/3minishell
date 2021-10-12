#!/bin/bash



./tt.sh 'ls'
./tt.sh 'ls
ls
ls'
export TT='tt.sh    echo.sh'
./tt.sh 'cat <$TT'
./tt.sh 'ls | wc > out.txt'
./tt.sh '<1test_all.sh cat | wc >out.txt'
./tt.sh '< 1test_all.sh cat | wc > out.txt'
./tt.sh 'cat < 1test_all.sh | > out.txt wc '
./tt.sh 'ls < 1test_all.sh | cat < tt.sh | > out.txt wc '
./tt.sh ' ls > out.txt | wc'
./tt.sh 'ls | wc'
ulimit -n 12
./tt.sh 'ls|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc'

./tt.sh '<Makefile cat | wc >out.txt'
./tt.sh '< Makefile cat | wc > out.txt'
./tt.sh 'cat < Makefile | > out.txt wc '
./tt.sh 'ls < Makefile | cat < Makefile | > out.txt wc '
./tt.sh 'cat < Makefile | cat < Makefile > out.txt | > out.txt wc '

./heredoc.sh
./cd.sh
./pwd.sh
./echo.sh
./exit.sh

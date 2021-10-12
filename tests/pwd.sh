#!/bin/bash

#./tt.sh 'cd'
./tt.sh 'pwd'
./tt.sh 'pwd ""'
./tt.sh 'pwd as;fajksldf;ja43340qfj`1e4=o 23]r	'

#LONG_PATH='dddddddd'
cp tt.sh ../minishell ~/goinfre/
cd ~/goinfre
#mkdir -p $LONG_PATH
#cd $LONG_PATH
#../tt.sh 'pwd'

#./tt.sh 'pwd'

#TODO $PATH for minishell

#cd ..
rm tt.sh minishell $LONG_PATH

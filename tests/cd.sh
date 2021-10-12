#!/bin/bash

#./tt.sh 'cd'
./tt.sh 'cd .'
./tt.sh 'cd ..'
./tt.sh 'cd ../libft'
./tt.sh 'cd /'
./tt.sh 'cd /bin'
./tt.sh 'cd /no_dir'
./tt.sh 'cd /bin/vi'
ln -s no_dir broken_link
./tt.sh 'cd broken_link'
rm broken_link

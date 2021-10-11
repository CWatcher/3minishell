#!/bin/bash

./tt.sh 'echo'
./tt.sh 'echo a'
./tt.sh 'echo "" ab'
./tt.sh 'echo ab ""'
./tt.sh 'echo -n'
./tt.sh 'echo -n a'

export TT='| ls'
./tt.sh 'echo $TT'
export TT='> out.txt'
./tt.sh 'echo $TT'
./tt.sh 'echo abc > out.txt'

# export TT='t    t'
# ./tt.sh 'echo "$TT"'
# export TT='t	t'
# ./tt.sh 'echo "$TT"'

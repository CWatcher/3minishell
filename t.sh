make > /dev/null || exit 1
echo 'make: ok!'

./tt.sh 'ls'
./tt.sh 'ls | wc'
ulimit -n 18
./tt.sh 'ls|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc|wc'
./tt.sh 'ls
ls
ls
ls'

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
./tt.sh 'exit'
./tt.sh 'echo abc > out.txt'
# ./tt.sh 'exit 0'
# ./tt.sh 'exit 1'
./tt.sh 'exit 2 1'
# ./tt.sh 'exit a'
# ./tt.sh 'exit 256'
# ./tt.sh 'exit 11111111111111111111111111111111'
# export TT='t    t'
# ./tt.sh 'echo "$TT"'
# export TT='t	t'
# ./tt.sh 'echo "$TT"'

make > /dev/null || exit 1
echo 'make: ok!'

./tt.sh 'ls'
./tt.sh 'ls | wc'
ulimit -n 7
./tt.sh 'ls | wc | wc | wc | wc | wc | wc | wc | wc | wc | wc | wc '
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

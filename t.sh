make > /dev/null || exit 1
echo 'make: ok!'

echo 'ls' | ./minishell
echo 'ls | wc' | ./minishell
ulimit -n 7
echo 'ls | wc | wc | wc | wc | wc | wc | wc | wc | wc | wc | wc ' | ./minishell

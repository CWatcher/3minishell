#!/bin/bash

echo "$1" | bash > out.0.txt
echo "$1" | ./minishell > out.1.txt

diff out.0.txt out.1.txt | cat -te \
	&& [ ${PIPESTATUS[0]} -eq 0 ] && echo 'ok!' \
	|| echo -e "------------\nfailed command:\n$1\n============"

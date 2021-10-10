#!/bin/bash

touch out.0.log err.0.log out.1.log err.1.log
echo "$1" | bash > out.0.log 2> err.0.log
echo 'Exit status =' $? >> out.0.log
echo "$1" | ./minishell > out.1.log 2> err.1.log
echo 'Exit status =' $? >> out.1.log

diff err.0.log err.1.log 1>&2
diff out.0.log out.1.log | cat -te \
	&& [ ${PIPESTATUS[0]} -eq 0 ] && echo 'ok!' \
	|| echo -e "------------\nfailed command:\n$1\n============"

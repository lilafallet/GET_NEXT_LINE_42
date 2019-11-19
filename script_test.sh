#!/bin/zsh

if test -f "$1" ; then
	VAR=0
	while [ $VAR -le 50 ]; do
		gcc -Wall -Wextra -Werror -fsanitize=address -g3 get_next_line.c get_next_line_utils.c TEST_main.c -I. -D BUFFER_SIZE=$VAR
		./a.out $1
		((VAR++))
		echo
	done
	rm a.out
else
	echo "Bad file"
	exit
fi

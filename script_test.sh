#!/bin/bash

if [ -v "$1" ]; then
	echo "Bad file"
	exit
else
	VAR=0
	MAX=$2
	if [ -z "$MAX" ]; then
		MAX=10
	fi
	while [ $VAR -le $MAX ]; do
		if [ $VAR != 0 ]; then
			echo
		fi
		gcc -Wall -Wextra -Werror -fsanitize=address -g3 get_next_line.c get_next_line_utils.c main.c -I. -D BUFFER_SIZE=$VAR
		if [ $? != 0 ]; then
			exit
		fi
		./a.out $1
		((VAR++))
	done
	rm -f a.out
fi

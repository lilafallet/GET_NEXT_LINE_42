# FT_GET_NEXT_LINE
This project is about to create a function that returns a line ending with a '\n' read from a file descriptor without knowing its size beforehand.
Bonus part : Manage multiple files.

# Building

``$> git clone https://github.com/lilafallet/GNL_42.git ``

``$> cd GNL_42``
   
   ``$> gcc -Wall -Wextra -Werror -I./includes/ main.c get_next_line.c get_next_line_utils.c``
   or
   
   ``$> gcc -Wall -Wextra -Werror -I./includes/ main_b.c get_next_line_bonus.c get_next_line_utils_bonus.c``
   
   ``./a.out``

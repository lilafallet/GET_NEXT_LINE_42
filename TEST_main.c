#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	int		fd;
	char	*line;
	int		ret;

	if (ac == 1)
		return (EXIT_FAILURE);
	line = NULL;
	fd = open(av[1], O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("line : |%s| ret : %d\n", line, ret);
		free(line);
		line = NULL;
	}
	printf("line : |%s| ret : %d\n", line, ret);
	close(fd);
	return (EXIT_SUCCESS);
}

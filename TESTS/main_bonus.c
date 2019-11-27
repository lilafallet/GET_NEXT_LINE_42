#include <fcntl.h>
#include <unistd.h>
#include "get_next_line_bonus.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*line1;
	char	*line2;
	char	*line3;
	int		ret1;
	int		ret2;
	int		ret3;

	if (ac != 4)
		return (EXIT_FAILURE);
	line1 = NULL;
	line2 = NULL;
	line3 = NULL;
	ret1 = 1;
	ret2 = 1;
	ret3 = 1;
	fd1 = open(av[1], O_RDONLY);
	fd2 = open(av[2], O_RDONLY);
	fd3 = open(av[3], O_RDONLY);
	while (ret1 > 0 || ret2 > 0 || ret3 > 0)
	{
		ret1 = get_next_line(fd1, &line1);
		ret2 = get_next_line(fd2, &line2);
		ret3 = get_next_line(fd3, &line3);
		if (line1 != NULL)
			printf("line1 : |%s| ret1 : %d\n", line1, ret1);
		if (line2 != NULL)
			printf("line2 : |%s| ret2 : %d\n", line2, ret2);
		if (line3 != NULL)
			printf("line3 : |%s| ret3 : %d\n", line3, ret3);
		free(line1);
		free(line2);
		free(line3);
		line1 = NULL;
		line2 = NULL;
		line3 = NULL;
	}
	printf("line1 : |%s| ret1 : %d\n", line1, ret1);
	printf("line2 : |%s| ret2 : %d\n", line2, ret2);
	printf("line3 : |%s| ret3 : %d\n", line3, ret3);
	free(line1);
	free(line2);
	free(line3);
	close(fd1);
	close(fd2);
	close(fd3);
	return (EXIT_SUCCESS);
}

#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		write(fd, s, ft_strlen(s));
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

int	main(int ac, char **av)
{
	int		fd;
	char	*line;
	int		ret;

	line = NULL;
	fd = open(av[1], O_RDONLY, 45);
	if (fd == -1)
		return (-1);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ft_putendl_fd(line, 1);
		free(line);
		line = NULL;
	}
	close(fd);
	return (EXIT_SUCCESS);
}

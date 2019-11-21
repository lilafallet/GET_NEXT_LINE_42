/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:30:10 by lfallet           #+#    #+#             */
/*   Updated: 2019/11/21 18:40:52 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h> //DEBUG

ssize_t		contained_newline(char *rest)
{
	ssize_t	i;

	i = 0;
	while (rest[i] != '\0')
	{
		if (rest[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		get_rest(char **rest, char **line)
{
	char	*tmp;
	char	*tmp2;
	ssize_t	i;
	int		ret;

	ret = 0;
	tmp = NULL;
	i = contained_newline(*rest);
	if (**rest != '\0')
	{
		ret = 1;
		if (i == -1)
			*line = ft_swap(&tmp, line, &tmp2, rest, (size_t)i, DO_LINE); //SWAP
		else
		{
			tmp2 = ft_swap(&tmp, line, &tmp2, rest, (size_t)i, DO_TMP2); //SWAP
			tmp = ft_swap(&tmp, line, &tmp2, rest, (size_t)i, DO_TMP); //SWAP
		}
	}
	free(*rest); //FREE
	*rest = tmp;
	return (ret);
}

int		read_line(int fd, char **rest, char **line)
{
	char	buff[BUFFER_SIZE + 1];
	int		ret;
	char	*tmp;
	char	*keep;

	keep = *rest;
	ft_memset(buff, 0, BUFFER_SIZE);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[BUFFER_SIZE] = '\0';
		tmp = *rest;
		*rest = ft_strjoin(tmp, buff, FREE_S1); //STRJOIN
		if (contained_newline(*rest) != -1)
			break ;
	}
	if (ret == 0 && (keep == NULL || *keep == '\0'))
	{
		if (*rest != NULL)
			get_rest(rest, line);
		free(*rest);
		return (0);
	}
	return ((ret != -1 && *rest != NULL) ? get_rest(rest, line) : ret);
}

int		get_next_line(int fd, char **line)
{
	static char	*rest = NULL;
	int			ret;

	ret = -1;
	if (fd >= 0)
	{
		*line = NULL;
		if (rest == NULL)
			ret = 0;
		else
			ret = get_rest(&rest, line);
		if (rest == NULL || *line == NULL)
			ret = read_line(fd, &rest, line);
	}
	return (ret);	
}

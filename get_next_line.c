/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:30:10 by lfallet           #+#    #+#             */
/*   Updated: 2019/11/18 21:07:50 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h> //DEBUG

int		get_rest(char **rest, char **line)
{
	char	*tmp;
	char	*tmp2;
	size_t	i;
	int		ret;

	i = 0;
	ret = 0;
	tmp = NULL;
	while ((*rest)[i] != '\0')
	{
		if ((*rest)[i] == '\n')
		{
			tmp = *line;
			*line = ft_strndup(*rest, i); //MEMCPY
			tmp2 = *line;
			*line = ft_strjoin(tmp, tmp2);
			free(tmp);
			free(tmp2);
			tmp = ft_strdup(*rest + i + 1); //MEMCPY
			ret = 1;
			break ;
		}
		i++;
	}
	if (i != 0 && ret == 0)
	{
		tmp2 = *line;
		*line = ft_strjoin(tmp2, *rest); //MEMCPY
		free(tmp2);
		ret = 1;
	}
	free(*rest); //FREE
	*rest = tmp;
	return (ret);
}

int		contained_newline(char *rest)
{
	size_t	i;

	i = 0;
	while (rest[i] != '\0')
	{
		if (rest[i] == '\n')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int		read_line(int fd, char **rest, char **line)
{
	char	buff[BUFFER_SIZE + 1];
	int		ret;
	char	*tmp;

	for (int i = 0; i < BUFFER_SIZE; i++) // ft_bzero
		buff[i] = 0;
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[BUFFER_SIZE] = '\0';
		tmp = *rest;
		*rest = ft_strjoin(tmp, buff); //utilisation STRJOIN
		free(tmp);
		if (contained_newline(*rest) == TRUE)
			break ;
	}
	if (ret != -1 && *rest != NULL)
	{
		get_rest(rest, line);
		return (*line != NULL);
	}
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	static char	*rest = NULL;
	int			ret;

	ret = -1;
	if (fd >= 0)
	{
		if (rest == NULL)
			ret = 0;
		else
			ret = get_rest(&rest, line);
		if (ret == 0)
			ret = read_line(fd, &rest, line);
	}
	return (ret);	
}

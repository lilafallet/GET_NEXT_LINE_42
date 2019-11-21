/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:30:10 by lfallet           #+#    #+#             */
/*   Updated: 2019/11/21 17:18:52 by lfallet          ###   ########.fr       */
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
	tmp2 = NULL;
	while ((*rest)[i] != '\0')
	{
		if ((*rest)[i] == '\n')
		{
			tmp2 = ft_swap(&tmp, line, &tmp2, rest, i, DO_TMP2); //SWAP
			tmp = ft_swap(&tmp, line, &tmp2, rest, i, DO_TMP); //SWAP
			ret = 1;
			break ;
		}
		i++;
	}
	if (i != 0 && ret == 0)
	{
		tmp2 = *line;
		*line = ft_strjoin(tmp2, *rest, FREE_S1); //STRJOIN
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
	char	*keep;

	keep = *rest;
	ft_memset(buff, 0, BUFFER_SIZE);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[BUFFER_SIZE] = '\0';
		tmp = *rest;
		*rest = ft_strjoin(tmp, buff, FREE_S1); //STRJOIN
		if (contained_newline(*rest) == TRUE)
			break ;
	}
	if (ret == 0 && (keep == NULL || *keep == '\0'))
	{
		if (*rest != NULL)
			get_rest(rest, line);
		free(*rest);
		return (0);
	}
	return ((ret != - 1 && *rest != NULL) ? get_rest(rest, line) : ret);
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

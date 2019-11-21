/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:30:10 by lfallet           #+#    #+#             */
/*   Updated: 2019/11/21 12:03:02 by lfallet          ###   ########.fr       */
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
			tmp = *line;
			tmp2 = ft_strndup(*rest, i); //STRNDUP
			//*line = ft_strjoin(tmp, tmp2); //STRJOIN
			*line = memjoin(tmp, tmp2, ft_strlen(tmp), ft_strlen(tmp2));
			//MEMJOIN 
			free(tmp); //FREE
			free(tmp2); //FREE
			tmp = ft_strdup(*rest + i + 1); //STRDUP
			ret = 1;
			break ;
		}
		i++;
	}
	if (i != 0 && ret == 0)
	{
		tmp2 = *line;
		//*line = ft_strjoin(tmp2, *rest); //STRJOIN
		*line = memjoin(tmp2, *rest, ft_strlen(tmp2), ft_strlen(*rest));
		//MEMJOIN 
		free(tmp2); //FREE
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
	for (int i = 0; i < BUFFER_SIZE; i++) // !!AJOUTER FT_BZERO!! //
		buff[i] = 0;
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[BUFFER_SIZE] = '\0';
		tmp = *rest;
		//*rest = ft_strjoin(tmp, buff); //STRJOIN
		printf("TEST1\n"); //DEBUG
		*rest = memjoin(tmp, buff, ft_strlen(tmp), ret); //MEMJOIN
		free(tmp); //FREE
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
	else if (ret != -1 && *rest != NULL)
		return (get_rest(rest, line));
	return (ret);
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

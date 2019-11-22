/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:30:10 by lfallet           #+#    #+#             */
/*   Updated: 2019/11/22 18:09:21 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h> //DEBUG

ssize_t		contained_newline(char *rest)
{
	ssize_t	i;

	i = 0;
	if (rest == NULL)
		return (-1);
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
	ssize_t	i;
	int		ret;

	ret = 0;
	if (*rest == NULL)
		return (ret);	
	i = contained_newline(*rest); //CONTAINED_NEWLINE
	tmp = NULL;
	if (**rest != '\0')
	{
		ret = 1;
		if (i == -1)
			*line = ft_strjoinfree(line, rest, FREE_S2); //STRJOINFREE
		else
		{
			tmp = ft_strndup(*rest, i); //STRNDUP
			*line = ft_strjoinfree(line, &tmp, FREE_S2); //STRJOINFREE
			tmp = ft_strndup(*rest + i + 1, ft_strlen(*rest + i + 1));
			//STRNDUP
		}
	}
	free(*rest); //FREE
	*rest = tmp;
	return (ret);
}

int		read_line(int fd, char **rest, char **line) //++FD--//
{
	char	buff[BUFFER_SIZE + 1];
	int		ret;
	char	*ptr_buff;
	char	*keep;

	keep = *rest;
	ft_memset(buff, 0, BUFFER_SIZE + 1); //MEMSET
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0) //READ //++FD--//
	{
		buff[BUFFER_SIZE] = '\0';
		ptr_buff = buff;
		*rest = ft_strjoinfree(rest, &ptr_buff, FREE_S1); //STRJOIN
		ft_memset(buff, 0, BUFFER_SIZE + 1); //MEMSET
		if (contained_newline(*rest) != -1) //CONTAINED_NEWLINE
			break ;
	}
	if (ret == 0 && (keep == NULL || *keep == '\0'))
	{
		get_rest(rest, line); //GET_REST
		free(*rest); //FREE
		return (0);
	}
	return ((ret != -1 && *rest != NULL) ? get_rest(rest, line) : ret);
	//GET_REST
}

int		get_next_line(int fd, char **line) //++FD--//
{
	static t_list	*lst = NULL;
	t_file			*file;
	int				ret;

	ret = -1;
	if (fd >= 0 && BUFFER_SIZE > 0 && BUFFER_SIZE < 8192000) //++FD--//
	{
		*line = NULL;
		file = get_file(&lst, fd);
		/* -> va creer le rest selon "l'index" fd. On va donc lui
			  envoyer le rest contenu dans lst et le file descriptor
		   -> La fonction va par la suite renvoyer le t_file FILE qui
			  va contenir le rest correspondant*/
		//if (file == NULL)
			//return (-1);
		ret = get_rest(&file->rest, line); //GET_REST
		if (file->rest == NULL || *line == NULL)
			ret = read_line(fd, &file->rest, line); //READ_LINE //++FD--//
		//if (ret < 1)
			//ft_del_node(&lst, file);
	}
	return (ret);	
}

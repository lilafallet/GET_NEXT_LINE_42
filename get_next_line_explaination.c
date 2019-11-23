/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_explaination.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:30:10 by lfallet           #+#    #+#             */
/*   Updated: 2019/11/23 19:37:48 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

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
	i = contained_newline(*rest);
	tmp = NULL;
	if (**rest != '\0')
	{
		ret = 1;
		if (i == -1)
			*line = ft_strjoinfree(line, rest, FREE_S2);
		else
		{
			tmp = ft_strndup(*rest, i);
			*line = ft_strjoinfree(line, &tmp, FREE_S2);
			tmp = ft_strndup(*rest + i + 1, ft_strlen(*rest + i + 1));
		}
	}
	free(*rest);
	*rest = tmp;
	return (ret);
}

int		read_line(int fd, char **rest, char **line)
{
	char	buff[BUFFER_SIZE + 1];
	int		ret;
	char	*ptr_buff;
	char	*keep;

	keep = *rest;
	ft_memset(buff, 0, BUFFER_SIZE + 1);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[BUFFER_SIZE] = '\0';
		ptr_buff = buff;
		*rest = ft_strjoinfree(rest, &ptr_buff, FREE_S1);
		ft_memset(buff, 0, BUFFER_SIZE + 1);
		if (contained_newline(*rest) != -1)
			break ;
	}
	if (ret == 0 && (keep == NULL || *keep == '\0'))
	{
		get_rest(rest, line);
		free(*rest);
		return (0);
	}
	return ((ret != -1 && *rest != NULL) ? get_rest(rest, line) : ret);
}

int		get_next_line(int fd, char **line)
{
	static t_list	*list = NULL; /*variable qui contient le
	reste*/
	t_file			*file; /*structure qui va contenir le reste
	correspondant au file descriptor*/
	int				ret; /*variable qui va contenir la valeur de retour*/

	ret = -1; /*si on ne passe pas par le if, la valeur de retour sera de -1 car il y aura eu une erreur*/
	if (line != NULL && fd >= 0 && BUFFER_SIZE > 0 &&
		BUFFER_SIZE < 8192000)
	/*pour rentrer dans le if il faut :
		- que line soit different de NULL
		- que le fd soit superieur ou egale a 0 car en dessous
		  de 0 il n y a pas de file descriptor
		- que le BUFFER_SIZE soit superieur de 0 car on ne peut
		  pas lire 0 caracteres
		- que le BUFFER_SIZE SOIT INFERIEUR A MB !!DEMANDER!!*/
	{
		*line = NULL; /*bien mettre le pointeur de line a NULL
		au cas ou il reste encore des caracteres dedans*/
		file = get_file(&list, fd);
		if (file == NULL)
			return (-1);
		ret = get_rest(&file->rest, line);
		if (file->rest == NULL || *line == NULL)
			ret = read_line(fd, &file->rest, line);
		if (ret < 1)
			del(&list, file);
	}
	return (ret);	
}

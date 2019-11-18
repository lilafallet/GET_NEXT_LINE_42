/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:30:10 by lfallet           #+#    #+#             */
/*   Updated: 2019/11/18 18:22:33 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_rest(char *rest)
{
	char	*str;
	char	*tmp;
	size_t	i;
	size_t	tmp_i;

	i = 0;
	while (rest[i] != '\0')
	{
		if (rest[i] == '\n')
		{
			tmp_i = i;
			while (rest[i] == '\n')
				i++;
			break ;
		}
		i++;
	}
	str = ft_memcpy(str, rest, tmp + 1) //MEMCPY
	str[tmp + 1] = '\0';
	tmp = ft_memcpy(tmp, rest + i, (ft_strlen(rest) - i) + 1); //MEMCPY
	free(rest); //FREE
	tmp[(ft_strlen(rest) - i) + 1] = '\0';
	rest = tmp;
	return (str); 
}

char	*read_line(int fd, char *rest)
{
	char	buff[BUFFER_SIZE + 1];
	int		ret;

	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[BUFFER_SIZE] = '\0';
		rest = ft_strjoin(rest, buff); //utilisation STRJOIN
	}
	return (rest);
}

int		is_backslach_n(char	*rest)
{
	while (rest[i] != '\0')
	{
		if (rest[i] =='\n')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int		get_next_line(int fd, char **line)
{
	static char	*rest = NULL;
	int			ret;

	if (*line == NULL || fd < 0)
		ret = -1;
	else
	{
		if (rest != NULL)
		{
			if (is_backslach_n(rest) == TRUE)
			{
				line = get_rest(&rest);
				ret = 1;
			}
			if (ret == 1)
				return (1);	
		}		
		rest = read_line(fd, &rest);
		if (is_backslach_n(rest) == TRUE)
		{
			line = get_rest(&rest);
			ret = 1;
		}
	}
	return (ret == 1 ? 1 : -1);	
}

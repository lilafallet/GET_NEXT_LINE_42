/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:53:46 by lfallet           #+#    #+#             */
/*   Updated: 2019/11/21 17:11:22 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //DEBUG

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

char	*ft_strndup(const char *s, size_t size)
{
	char	*str;
	size_t	len_str;

	len_str = ft_strlen(s); //STRLEN
	if (size > len_str)
		size = len_str;
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (str != NULL)
	{
		ft_memcpy(str, s, size); //MEMCPY
		str[size] = '\0';
	}
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2, int is_free)
{
	char	*str;
	size_t	len_str;

	str = NULL;
	if (s1 != NULL && s2 != NULL)
	{
		len_str = ft_strlen(s1) + ft_strlen(s2);
		str = (char *)malloc(sizeof(char) * (len_str + 1));
		if (str != NULL)
		{
			ft_memcpy(str, s1, ft_strlen(s1)); //MEMCPY
			ft_memcpy(str + ft_strlen(s1), s2, ft_strlen(s2)); //MEMCPY
			str[len_str] = '\0';
		}
	}
	if (s1 == NULL)
		str = ft_strndup(s2, ft_strlen(s2)); //STRNDUP
	if (s2 == NULL)
		str = ft_strndup(s1, ft_strlen(s1)); //STRNDUP
	if (is_free == FREE_S1 || is_free == FREE_S1_S2)
		free((char *)s1); //FREE
	if (is_free == FREE_S2 || is_free == FREE_S1_S2)
		free((char *)s2); //FREE
	return (str);
}

char	*ft_swap(char **tmp, char **line, char **tmp2, char **rest,
		int i, int do_what)
{
	if (do_what == DO_LINE)
	{
		*tmp = *line;
		return (ft_strndup(*rest, i));
	}
	*line = ft_strjoin(*tmp, *tmp2, FREE_S1_S2);
	return (ft_strndup(*rest + i + 1, ft_strlen(*rest) - i));
}

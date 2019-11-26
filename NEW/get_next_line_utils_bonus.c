/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 21:24:52 by lfallet           #+#    #+#             */
/*   Updated: 2019/11/26 21:25:00 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void		*ft_memset(void *s, int c, size_t n)
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

size_t		ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

static void	*ft_memcpy(void *dest, const void *src, size_t n)
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

char		*ft_strndup(const char *s, size_t size)
{
	char	*str;
	size_t	len_str;

	if (s == NULL)
		return (NULL);
	len_str = ft_strlen(s);
	if (size > len_str)
		size = len_str;
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (str != NULL)
	{
		ft_memcpy(str, s, size);
		str[size] = '\0';
	}
	return (str);
}

char		*ft_strjoinfree(char **s1, char **s2, int is_free)
{
	char	*str;
	size_t	len_str;

	if (*s1 != NULL && *s2 != NULL)
	{
		len_str = ft_strlen(*s1) + ft_strlen(*s2);
		str = (char *)malloc(sizeof(char) * (len_str + 1));
		if (str != NULL)
		{
			ft_memcpy(str, *s1, ft_strlen(*s1));
			ft_memcpy(str + ft_strlen(*s1), *s2, ft_strlen(*s2));
			str[len_str] = '\0';
		}
	}
	else
		str = *s1 == NULL ? ft_strndup(*s2, ft_strlen(*s2)) :
			ft_strndup(*s1, ft_strlen(*s1));
	free(*s1);
	*s1 = NULL;
	if (is_free == FREE_S2)
	{
		free(*s2);
		*s2 = NULL;
	}
	return (str);
}

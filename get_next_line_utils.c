/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:53:46 by lfallet           #+#    #+#             */
/*   Updated: 2019/11/19 14:12:11 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	len_str;

	len_str = ft_strlen(s); //STRLEN
	str = (char *)malloc(sizeof(char) * (len_str + 1));
	if (str != NULL)
	{
		ft_memcpy(str, s, len_str); //MEMCPY
		str[len_str] = '\0';
	}
	return (str);
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;
	size_t	len_str;

	str = NULL;
	if (s1 != NULL && s2 != NULL)
	{
		len_s1 = ft_strlen(s1);
		len_s2 = ft_strlen(s2);
		len_str = len_s1 + len_s2;
		str = (char *)malloc(sizeof(char) * (len_str + 1));
		if (str != NULL)
		{
			ft_memcpy(str, s1, len_s1); //MEMCPY
			ft_memcpy(str + len_s1, s2, len_s2); //MEMCPY
			str[len_str] = '\0';
		}
	}
	else if (s1 == NULL)
		str = ft_strdup(s2); //STRDUP
	else if (s2 == NULL)
		str = ft_strdup(s1); //STRDUP
	return (str);
}


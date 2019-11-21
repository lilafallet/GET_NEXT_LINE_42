/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:28:57 by lfallet           #+#    #+#             */
/*   Updated: 2019/11/21 17:18:52 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# define TRUE 1
# define FALSE 0
# define FREE_S1 1
# define FREE_S2 2
# define FREE_S1_S2 3
# define DO_TMP2 1
# define DO_TMP 2
# define DO_LINE 3

int		get_next_line(int fd, char **line);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2, int is_free);
char	*ft_strndup(const char *s, size_t size);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_swap(char **tmp, char **line, char **tmp2, char **rest,
		int i, int do_what);

# endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:45:38 by lfallet           #+#    #+#             */
/*   Updated: 2019/11/23 09:57:29 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*create_new_list(void *content)
{
	t_list	*elem;

	elem = (t_list *)malloc(sizeof(t_list));
	if (elem != NULL)
	{
		elem->content = content;
		elem->next = NULL;
	}
	return (elem);
}

int		create_new_file(t_list **lst, int fd)
{
	t_file	*file;
	t_list	*elem;

	file = (t_file *)malloc(sizeof(t_file));
	if (file == NULL)
		return (-1);
	file->fd = fd;
	file->rest = NULL;
	elem = create_new_list(file);
	if (elem == NULL)
	{
		free(file);
		return (-1);
	}
	elem->next = *lst;
	*lst = elem;
	return (0);
}

t_file *get_file(t_list **lst, int fd)
{
	t_list	*run;

	run = *lst;
	while (run != NULL)
	{
		if (((t_file *)(run->content))->fd == fd)
			return ((t_file *)(run->content));
		run = run->next;
	}
	if (create_new_file(lst, fd) == -1)
		return (NULL);
	return ((t_file *)((*lst)->content));
}

void	del(t_list **lst, t_file *file)
{
	t_list	*run;
	t_list	*tmp;

	run = *lst;
	tmp = run;
	while (run != NULL)
	{
		if ((t_file *)(run->content) == file)
		{
			tmp->next = run->next;
			free(((t_file *)(run->content))->rest);
			free(run->content);
			if (run == *lst)
				*lst = run->next;
			free(run);
			return ;
		}
		tmp = run;
		run = run->next;
	}
}

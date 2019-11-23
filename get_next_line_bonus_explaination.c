/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus_explaination.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:45:38 by lfallet           #+#    #+#             */
/*   Updated: 2019/11/23 19:40:59 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*create_new_list(void *content)
{
	t_list	*elem;

	elem = (t_list *)malloc(sizeof(t_list)); /*faire un malloc de
	la taille de la stucture t_list (content)*/
	if (elem != NULL)
	{
		elem->content = content; /*dans la stucture t_list,
		content vaut maintenant le rest et le fd de content, qui
		est contenu dans la structure t_file file*/
		elem->next = NULL;
	}
	return (elem);
}

int		create_new_file(t_list **lst, int fd)
{
	t_file	*file;
	t_list	*elem;

	file = (t_file *)malloc(sizeof(t_file)); /*faire un malloc
	de la taille de la structure t_file (rest et fd)*/
	if (file == NULL)
		return (-1);
	file->fd = fd;
	file->rest = NULL;
	elem = create_new_list(file); /*envoie a la fonction qui va
	creer la liste, la structure t_file file qui contient donc
	le rest et le fd.*/
	if (elem == NULL)
	{
		free(file);
		return (-1);
	}
	elem->next = *lst; /*le t_list elem qui pointe sur la
	prochaine structure s_list vaut le static rest*/
	*lst = elem; /*puis le static rest devient le t_list elem
	avec le file descriptor et le rest qui correspond*/
	return (0);
}

t_file *get_file(t_list **lst, int fd)
{
	/*/!\ dans le cas ou list == NULL*/
	/* --> dans le cas ou list est != NULL*/

	t_list	*run;

	run = *lst; /* si /!\ run == NULL*/
	while (run != NULL)
	{
		if (((t_file *)(run->content))->fd == fd)
			return ((t_file *)(run->content));
		run = run->next;
	}
	if (create_new_file(lst, fd) == -1) 
		return (NULL); /*rentre dans cette condition si le
		malloc de file (dans create_new_file) a echoue ou si le
		malloc de elem (dans create_new_list) a echoue*/  
	return ((t_file *)((*lst)->content)); /*si toutes les bonnes
	conditions sont remplies, on renvoie dans get_next_line, qui
	sera file -> renvoie le pointeur t_list sur lst qui contient
	maintenant le s_file avec le rest et le file descriptor a
	travers le content*/
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

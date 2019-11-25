/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_explaination.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:30:10 by lfallet           #+#    #+#             */
/*   Updated: 2019/11/25 16:27:00 by lfallet          ###   ########.fr       */
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
		return (ret); /*on retourne donc 0*/
	i = contained_newline(*rest); /*on recupere l'index de ou se
	trouve le '\n'* ou le retour -1 si il n'y en a pas*/
	tmp = NULL;
	if (**rest != '\0') /*rentre dans cette condition si rest
	contient quelque chose*/
	{
		ret = 1; /*si on rentre dans cette condition le retour
		vaudra 1 car si on est arrive ici c'est qu'on a lue une
		ligne*/
		if (i == -1) /*rentre dans cette condition si :
		- rest ne contient pas de '\n'*/
			*line = ft_strjoinfree(line, rest, FREE_S2); /*line
			va maintenant valoir le rejoignement de line et du
			rest, et on free rest*/
		else /*rentre dans le cas ou rest contient un '\n'*/
		{
			tmp = ft_strndup(*rest, i); /*tmp va valoir le reste
			jusqu'au caractere avant le '\n'*/
			*line = ft_strjoinfree(line, &tmp, FREE_S2); /*line
			va maintenant valoir le rejoignement de line et tmp
			(le reste jusqu'au caractere avant le '\n') et on
			free tmp*/
			tmp = ft_strndup(*rest + i + 1, ft_strlen(*rest + i + 1)); /*tmp va donc valoir le rest a partir du caractere apres
	   '\n'*/
		}
	}
	free(*rest); 
	*rest = tmp; /*rest vaut maintenant tmp*/
	return (ret);
}

int		read_line(int fd, char **rest, char **line)
{
	char	buff[BUFFER_SIZE + 1]; /*variable qui va stocker ce
	qui a ete lue*/
	int		ret;
	char	*ptr_buff; /*temporaire de buff*/
	char	*keep; /*temporaire du rest (dans le file)*/

	keep = *rest;
	ft_memset(buff, 0, BUFFER_SIZE + 1); /*cleaner buff*/
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0) 
	{
		buff[BUFFER_SIZE] = '\0';
		ptr_buff = buff;
		*rest = ft_strjoinfree(rest, &ptr_buff, FREE_S1);
		/*va relier le rest et ce qui a ete lue et va free le
		rest et le mettre a NULL. Le rest devient donc
		le rest + ce qui a ete lue*/
		ft_memset(buff, 0, BUFFER_SIZE + 1); /*cleaner buff*/
		if (contained_newline(*rest) != -1) /*si rest contient
		'\n' on sort de la boucle. Dans le cas inverse, on
		contenue de lire tant qu'on ne trouve pas de '\n dans la
		lecture*/
			break ;
	}
	if (ret == 0 && (keep == NULL || *keep == '\0'))
	/*rendre dans cette condition si :
		- si on a lu tout le document texte
		- si keep (donc rest) est a NULL ou contient juste un 
			'\0'*/
	{
		get_rest(rest, line); 
		free(*rest);
		return (0); /*on appelle la fonction get_rest pour
		recuperer le reste, mais a la difference des autres
		appels, on libere le rest et on renvoie bien 0 pour
		annoncer qu'on a fini le fichier*/
	}
	return ((ret != -1 && *rest != NULL) ? get_rest(rest, line) : ret); /*si ret est different de -1 et que le rest de depart
		n'est pas egale a NULL (soit que le fichier a ete lu 
		entierement ou qu'une ligne a ete lu), on appelle la
		fonction get rest pour avoir le rest.
		Dans le cas contraire, on renvoie tout simplement le
		retour (-1, 0 ou 1)*/
}

int		get_next_line(int fd, char **line)
{
	static t_list	*list = NULL; /*pointeur sur une liste qui
	contient la structure qui contient content (qui contiendra
	le rest et le fd)*/
	t_file			*file; /*pointeur sur la structure qui va contenir le reste correspondant au file descriptor*/
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
		file = get_file(&list, fd); /*la variable file
		contient donc le rest correspondant au file	descriptor*/
		if (file == NULL) /*dans le cas ou le malloc de file
		dans la fonction create_new_file echoue, elle va
		retourner -1 a la fonction get_file et donc la variable
		file va donc valoir NULL*/
			return (-1); /*il va donc il y avoir une erreur*/
		ret = get_rest(&file->rest, line); /*la variable ret va
		contenir le retour de read dans la fonction get_rest*/
		/*on va envoyer a la fonction get_rest l'adresse du
		t_file file qui contient le rest mais aussi la ligne
		de lecture*/
		if (file->rest == NULL || *line == NULL) /*on rentre
		dans cette condition la premiere fois que l'on rentre
		dans la fonction get_next_line au debut de chaque
		ouverture de file descriptor, c'est a dire quand le rest
		est egale a NULL. Ou aussi dans le cas ou la ligne en
		cours est egale a NULL*/
			ret = read_line(fd, &file->rest, line); /*on envoie
		a la fonction qui va lire la ligne le file descriptor et
		donc le reste en fonction de ce file descriptor puis
		finalement la ligne a lire*/
		if (ret < 1) /*dans le cas ou il y a eu une erreur (-1)
		ou que le fichier a ete lue entierement (0)*/
			del(&list, file);
	}
	return (ret);	
}

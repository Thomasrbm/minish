/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcards2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:07:47 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 04:32:19 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Retourne 1 si la chaîne contient '*' ; 0 sinon */
int	contains_wildcard(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

/* Crée un noeud à partir du nom d'une entrée. */
/* Ne prend que 2 paramètres */
t_list	*create_node_from_entry(char *entry_name, t_list **lst)
{
	t_list	*new_node;

	new_node = ft_lstnew(ft_strdup(entry_name));
	if (!new_node)
	{
		ft_lstclear(lst, free);
	}
	return (new_node);
}

/* Process_entry : 4 paramètres : p, lst, e et wc.
   Retourne 0 en succès, -1 en erreur.
*/
static int	process_entry(char *p, t_list **lst, struct dirent *e,
		t_wildcard *wc)
{
	t_list	*node;

	if (e->d_name[0] == '.' && (p[0] != '.' || (p[0] == '*' && p[1] != '.')))
		return (0);
	if (wildcard_match(p, e->d_name, wc))
	{
		node = create_node_from_entry(e->d_name, lst);
		if (!node)
			return (-1);
		ft_lstadd_back(lst, node);
	}
	return (0);
}

/* Fonction principale d'expansion */
t_list	*expand_arg_list(char *p)
{
	DIR				*dir;
	struct dirent	*e;
	t_list			*lst;
	t_wildcard		wc;

	lst = NULL;
	wc.star = -1;
	wc.match = 0;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	e = readdir(dir);
	while (e != NULL)
	{
		if (process_entry(p, &lst, e, &wc) < 0)
		{
			closedir(dir);
			return (NULL);
		}
		e = readdir(dir);
	}
	closedir(dir);
	return (lst);
}

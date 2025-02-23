/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:33:19 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 04:25:35 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_list	*process_argument(char *arg)
{
	t_list	*lst;

	if (contains_wildcard(arg))
	{
		lst = expand_arg_list(arg);
		if (lst)
			return (lst);
		else
			return (ft_lstnew(ft_strdup(arg)));
	}
	else
		return (ft_lstnew(ft_strdup(arg)));
}

t_list	*expand_wildcards_list(char **cmd)
{
	int		i;
	t_list	*result;
	t_list	*arg_lst;
	t_list	*tmp_node;

	result = NULL;
	i = 0;
	while (cmd[i])
	{
		arg_lst = process_argument(cmd[i]);
		tmp_node = arg_lst;
		while (tmp_node)
		{
			ft_lstadd_back(&result, ft_lstnew(ft_strdup(tmp_node->content)));
			tmp_node = tmp_node->next;
		}
		ft_lstclear(&arg_lst, free);
		i++;
	}
	return (result);
}

char	**lst_to_tab(t_list *lst)
{
	int		size;
	char	**tab;
	int		i;
	t_list	*tmp;

	size = ft_lstsize(lst);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	i = 0;
	tmp = lst;
	while (tmp)
	{
		tab[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

char	**expand_wildcards(char **cmd)
{
	char	**tab;
	t_list	*lst;

	lst = expand_wildcards_list(cmd);
	tab = lst_to_tab(lst);
	ft_lstclear(&lst, free);
	return (tab);
}

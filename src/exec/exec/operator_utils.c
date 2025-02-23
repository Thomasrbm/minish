/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:39:08 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 00:39:19 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_operator(char *token, int *pos, int *op_type, int j)
{
	if (!ft_strcmp(token, "&&"))
	{
		*pos = j;
		*op_type = AND_NODE;
	}
	else if (!ft_strcmp(token, "||"))
	{
		*pos = j;
		*op_type = OR_NODE;
	}
}

int	find_split_pos(char **tokens, int *op_type)
{
	int	j;
	int	paren;
	int	pos;

	j = 0;
	paren = 0;
	pos = -1;
	*op_type = 0;
	while (tokens[j])
	{
		if (!ft_strcmp(tokens[j], "("))
			paren++;
		else if (!ft_strcmp(tokens[j], ")"))
			paren--;
		else if (paren == 0)
			check_operator(tokens[j], &pos, op_type, j);
		j++;
	}
	return (pos);
}

int	fill_ast_operator_tokens(t_ast *node, char **t, int sp)
{
	char	**l;
	char	**r;

	l = dup_tokens(t, 0, sp - 1);
	r = dup_tokens(t, sp + 1, -1);
	if (!l || !r)
	{
		free_tab(l);
		free_tab(r);
		return (1);
	}
	node->left = build_ast(l);
	node->right = build_ast(r);
	free_tab(l);
	free_tab(r);
	if (!node->left || !node->right)
	{
		free_ast(node);
		return (1);
	}
	return (0);
}

int	fill_ast_operator(t_ast *node, char **t, int sp, int op)
{
	if (op == AND_NODE)
		node->type = AND_NODE;
	else
		node->type = OR_NODE;
	node->cmd = NULL;
	return (fill_ast_operator_tokens(node, t, sp));
}

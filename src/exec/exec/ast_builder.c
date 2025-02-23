/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:38:31 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 08:39:23 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_ast	*build_ast_operator(char **t, int sp, int op)
{
	t_ast	*node;

	(void)t;
	(void)sp;
	(void)op;
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	// if (fill_ast_operator(node, t, sp, op) != 0)
	// 	return (NULL);
	return (node);
}

t_ast	*handle_parentheses(char **tokens, int size)
{
	char	**new_tokens;
	t_ast	*node;

	new_tokens = dup_tokens(tokens, 1, size - 2);
	node = build_ast(new_tokens);
	free_tab(new_tokens);
	return (node);
}

t_ast	*build_ast_cmd(char **tokens)
{
	t_ast	*node;
	int		size;

	if (!tokens || !*tokens)
		return (NULL);
	size = tab_size(tokens);
	if (size >= 2 && !ft_strcmp(tokens[0], "(") && !ft_strcmp(tokens[size - 1],
			")"))
		return (handle_parentheses(tokens, size));
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = CMD_NODE;
	node->left = NULL;
	node->right = NULL;
	node->cmd = ft_tabdup(tokens);
	if (!node->cmd)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

t_ast	*build_ast(char **tokens)
{
	int		split_pos;
	int		op_type;
	t_ast	*node;

	if (!tokens || !*tokens)
		return (NULL);
	split_pos = find_split_pos(tokens, &op_type);
	if (split_pos != -1)
		node = build_ast_operator(tokens, split_pos, op_type);
	else
		node = build_ast_cmd(tokens);
	return (node);
}

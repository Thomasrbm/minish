/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:50:53 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 06:59:30 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->type == CMD_NODE && node->cmd)
		free_tab(node->cmd);
	free(node);
}

static void	execute_tokens(t_shell *shell, char **toks)
{
	t_ast	*ast;

	shell->cmd = free_tab(shell->cmd);
	shell->cmd = expand_wildcards(toks);
	free_tab(toks);
	if (shell->cmd && shell->cmd[0] && shell->cmd[0][0] != '\0')
	{
		ast = build_ast(shell->cmd);
		if (!ast)
		{
			error_message(shell->cmd);
			shell->exit_code = 127;
		}
		else
		{
			shell->exit_code = exec_ast(ast, shell);
			free_ast(ast);
		}
	}
	else
	{
		error_message(shell->cmd);
		shell->exit_code = 127;
	}
}

int	handle_cycle(t_shell *shell)
{
	char	**toks;

	toks = process_input_line(shell);
	if (!toks)
		return (-1);
	execute_tokens(shell, toks);
	shell->cmd = free_tab(shell->cmd);
	return (0);
}

int	shell_loop(t_shell *shell)
{
	int	exit_code;

	shell->exit_code = 0;
	while (1)
	{
		shell->pipe_count = 0;
		shell->check = 0;
		shell->save_in = 0;
		shell->size = 0;
		shell->save_out = 0;
		shell->in_count = 0;
		shell->out_count = 0;
		exit_code = handle_cycle(shell);
		if (exit_code == -1)
			break ;
	}
	clear_history();
	free_tab(shell->env);
	exit_code = shell->exit_code;
	free(shell);
	return (exit_code);
}

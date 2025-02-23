/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:34:46 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 02:29:08 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strjoin_free_both(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

int	fork_and_exec(t_ast *ast, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("fork", 2);
		return (127);
	}
	if (pid == 0)
	{
		setup_signals(0);
		status = exec_cmd_external(ast->cmd, shell);
		free(ast);
		exit(status);
	}
	return (wait_ignore(pid));
}

int	exec_ast_cmd_node(t_ast *ast, t_shell *shell)
{
	int	ret;

	ret = validate_cmd(ast);
	if (ret)
		return (ret);
	if (is_redirection(shell) == 0)
		return (redirect(shell, ast));
	if (is_builtin(shell)->check == 0)
		return (exec_builtin(ast->cmd, shell, ast));
	if (check_single_cmd(shell))
		return (shell->exit_code);
	ret = check_additional_cmd(ast, shell);
	if (ret)
		return (ret);
	return (fork_and_exec(ast, shell));
}

int	exec_ast(t_ast *ast, t_shell *shell)
{
	int	status;

	if (!ast)
		return (1);
	if (ast->type == CMD_NODE)
		return (exec_ast_cmd_node(ast, shell));
	status = exec_ast(ast->left, shell);
	if ((ast->type == AND_NODE && status == 0) || (ast->type == OR_NODE
			&& status != 0))
		return (exec_ast(ast->right, shell));
	return (status);
}

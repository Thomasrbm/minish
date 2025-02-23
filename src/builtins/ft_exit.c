/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 22:55:53 by rbardet-          #+#    #+#             */
/*   Updated: 2025/02/22 17:02:35 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// exit error message in case the exit code contain a non numeric
// argument.
void	exit_error_message(t_shell *shell, t_ast *ast)
{
	ft_putstr_fd("Minishell: exit: ", 2);
	ft_putstr_fd(shell->cmd[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_exit(shell, ast);
	exit(2);
}

// exit free function to cause no memory leak
void	free_exit(t_shell *shell, t_ast *ast)
{
	if (shell->cmd)
		free_tab(shell->cmd);
	if (shell->env)
		free_tab(shell->env);
	if (ast && ast->cmd)
		free_tab(ast->cmd);
	if (ast)
		free(ast);
	free(shell);
}

// process the verification if the exit value is valid or no
long long	exit_limits(t_shell *shell, t_ast *ast, int i, long long status)
{
	if (shell->cmd[1][0] == '-')
		i = 1;
	if (shell->cmd[1][0] == '-' && shell->cmd[1][1] == '\0')
		exit_error_message(shell, ast);
	while (shell->cmd[1][i] != '\0')
	{
		if (!isdigit(shell->cmd[1][i]))
			exit_error_message(shell, ast);
		i++;
	}
	return (status);
}

// exit funtion main, quit the program if there is not too many arguments.
long long	ft_exit(t_shell *shell, t_ast *ast)
{
	long long	status;
	int			error;
	int			i;

	i = 0;
	ft_putstr_fd("exit\n", 2);
	if (tab_size(shell->cmd) > 2)
	{
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (!shell->cmd[1])
	{
		status = shell->exit_code;
		free_exit(shell, ast);
		exit(status);
	}
	status = ft_atol_safe(shell->cmd[1], &error);
	if (error)
		exit_error_message(shell, ast);
	status = exit_limits(shell, ast, i, status);
	free_exit(shell, ast);
	exit (status);
}

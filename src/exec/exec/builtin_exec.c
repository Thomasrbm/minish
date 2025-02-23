/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:39:32 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 05:31:52 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_builtin(char **cmd, t_shell *shell, t_ast *ast)
{
	if (!cmd || !cmd[0])
		return (shell->exit_code = 127, 127);
	if (!ft_strcmp(cmd[0], "cd"))
		shell = ft_cd(shell);
	else if (!ft_strcmp(cmd[0], "pwd"))
		shell->exit_code = ft_pwd();
	else if (!ft_strcmp(cmd[0], "export"))
		shell = ft_export(shell);
	else if (!ft_strcmp(cmd[0], "unset"))
		shell = ft_unset(shell);
	else if (!ft_strcmp(cmd[0], "env"))
		shell->exit_code = ft_env(shell);
	else if (!ft_strcmp(cmd[0], "echo"))
		shell = ft_echo(shell->cmd, shell);
	else if (!ft_strcmp(cmd[0], "exit"))
		shell->exit_code = ft_exit(shell, ast);
	else
		return (shell->exit_code = 127);
	return (shell->exit_code);
}

char	*get_env_value(char *var, t_shell shell)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(var);
	while (shell.env[i])
	{
		if (!ft_strncmp(shell.env[i], var, len) && shell.env[i][len] == '=')
			return (ft_strdup(shell.env[i] + len + 1));
		i++;
	}
	return (NULL);
}

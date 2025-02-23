/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:35:59 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 04:53:33 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	validate_cmd_initial(t_ast *ast)
{
	if (!ast->cmd || !ast->cmd[0])
		return (1);
	if (!ft_strcmp(ast->cmd[0], "/"))
	{
		error_message(ast->cmd);
		free_tab(ast->cmd);
		ast->cmd = NULL;
		return (127);
	}
	if (!ft_strcmp(ast->cmd[0], ".") || !ft_strcmp(ast->cmd[0], ".."))
	{
		error_message(ast->cmd);
		return (127);
	}
	return (0);
}

int	validate_cmd(t_ast *ast)
{
	int		ret;
	char	*trim;

	ret = validate_cmd_initial(ast);
	if (ret)
		return (ret);
	trim = ft_strtrim(ast->cmd[0], " \t\n");
	if (ft_strcmp(ast->cmd[0], trim) != 0)
	{
		error_message(ast->cmd);
		free(trim);
		free_tab(ast->cmd);
		ast->cmd = NULL;
		return (127);
	}
	free(trim);
	return (0);
}

int	check_additional_cmd(t_ast *ast, t_shell *shell)
{
	if (ast->cmd[1] && !ft_strchr(ast->cmd[0], '/') && check_first(ast->cmd[0],
			shell->env))
	{
		error_message(ast->cmd);
		shell->exit_code = 127;
		free_tab(ast->cmd);
		ast->cmd = NULL;
		return (127);
	}
	return (0);
}

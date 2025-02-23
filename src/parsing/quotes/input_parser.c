/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:51:58 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 08:13:15 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	parse_state0(char *in, int *i, char **res, t_shell *shell)
{
	int	idx[4];

	{
		idx[0] = *i;
		idx[1] = 0;
		idx[2] = 0;
		idx[3] = 0;
		process_default_state(in, idx);
		*i = idx[0];
		if (!in[*i])
			return (0);
	}
	if (in[*i] == '\'')
		return (1);
	if (in[*i] == '"')
		return (2);
	if (in[*i] == '$')
	{
		handle_dollar(in, i, res, shell);
		return (0);
	}
	*res = append_char(*res, in[*i]);
	return (0);
}

static int	parse_state1(char *in, int *i, char **res)
{
	if (in[*i] == '\'')
		return (0);
	*res = append_char(*res, in[*i]);
	return (1);
}

static void	handle_state2_dollar(char *in, int *i, char **res, t_shell *shell)
{
	char	*tmp;
	char	*var;
	int		start;

	if (in[*i + 1] == '?')
	{
		tmp = ft_itoa(shell->exit_code);
		*res = append_str(*res, tmp);
		free(tmp);
		(*i)++;
	}
	else
	{
		start = *i + 1;
		while (in[*i + 1] && (ft_isalnum(in[*i + 1]) || in[*i + 1] == '_'))
			(*i)++;
		tmp = ft_substr(in, start, *i - start + 1);
		var = get_env_value(tmp, *shell);
		free(tmp);
		*res = append_str(*res, var);
		free(var);
	}
}

static int	parse_state2(char *in, int *i, char **res, t_shell *shell)
{
	if (in[*i] == '"')
		return (0);
	if (in[*i] == '$')
	{
		handle_state2_dollar(in, i, res, shell);
		return (2);
	}
	*res = append_char(*res, in[*i]);
	return (2);
}

/* Appel de is_full_quoted + validate_syntax + parse_cmd */
char	*ft_parse_input(char *in, t_shell *shell)
{
	if (validate_syntax(shell, in))
	{
		return (ft_strdup(""));
	}
	return (parse_cmd(in));
}

char	*ft_parser_main(char *in, t_shell *shell)
{
	char	*res;
	int		state;
	int		i;

	res = ft_strdup("");
	state = 0;
	i = 0;
	while (in[i])
	{
		if (state == 0)
			state = parse_state0(in, &i, &res, shell);
		else if (state == 1)
			state = parse_state1(in, &i, &res);
		else if (state == 2)
			state = parse_state2(in, &i, &res, shell);
		if (in[i])
			i++;
	}
	if (state != 0)
	{
		free(res);
		return (ft_strdup(""));
	}
	return (res);
}

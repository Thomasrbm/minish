/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_preprocess.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:52:05 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 08:06:44 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*read_and_trim(t_shell *shell)
{
	char	*in;
	char	*trim;

	in = get_readline(shell);
	if (!in)
	{
		ft_putstr_fd("exit\n", 2);
		return (NULL);
	}
	trim = ft_strtrim(in, " \n\t");
	free(in);
	if (!trim)
		return (NULL);
	if (!*trim)
		trim[0] = '\0';
	return (trim);
}

void	remove_markers(char **toks)
{
	int		i;
	char	*tmp;

	i = 0;
	while (toks && toks[i])
	{
		tmp = remove_marker(toks[i]);
		free(toks[i]);
		toks[i] = tmp;
		i++;
	}
}

char	**process_input_line(t_shell *shell)
{
	char	*trim;
	char	**toks;

	trim = read_and_trim(shell);
	if (!trim)
		return (NULL);
	trim = ft_parse_input(trim, shell);
	if (!trim)
		return (NULL);
	toks = ft_tokenize_line(trim, shell);
	free(trim);
	remove_markers(toks);
	return (toks);
}

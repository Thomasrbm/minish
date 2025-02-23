/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:48:48 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 07:16:47 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_quotes_state(char c, int *in_s, int *in_d)
{
	if (c == '\'' && !(*in_d))
		*in_s = !(*in_s);
	else if (c == '"' && !(*in_s))
		*in_d = !(*in_d);
}

static void	copy_no_quotes(const char *s, char *dest)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '"') && (i == 0 || s[i - 1] != '\\'))
		{
			update_quotes_state(s[i], &(int){0}, &(int){0});
			i++;
		}
		else
		{
			dest[j] = s[i];
			i++;
			j++;
		}
	}
	dest[j] = '\0';
}

char	*remove_quotes(char *s)
{
	char	*clean;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	clean = malloc(len + 1);
	if (!clean)
		return (NULL);
	copy_no_quotes(s, clean);
	return (clean);
}

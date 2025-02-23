
#include "../../minishell.h"

int	all_quotes_closed(char *s)
{
	int	in_s;
	int	in_d;
	int	in_bt;
	int	i;

	in_s = 0;
	in_d = 0;
	in_bt = 0;
	i = 0;
	while (s[i])
	{
		/* Si le caractère n'est pas une quote, on passe */
		if (s[i] != '\'' && s[i] != '"' && s[i] != '`')
		{
			i++;
			continue ;
		}
		/* Inverse le flag pour chaque quote rencontrée */
		if (s[i] == '\'')
			in_s = !in_s;
		else if (s[i] == '"')
			in_d = !in_d;
		else if (s[i] == '`')
			in_bt = !in_bt;
		i++;
	}
	/* Si la chaîne contient uniquement des quotes, on la considère fermée */
	if (!in_s && !in_d && !in_bt && is_only_quotes(s))
		return (1);
	return (!in_s && !in_d && !in_bt);
}

int	is_full_quoted(char *s)
{
	size_t	len;

	if (!s || !*s)
		return (0);
	len = ft_strlen(s);
	/* Si la chaîne est exactement deux quotes identiques, c'est vide */
	if (len == 2 && ((s[0] == '"' && s[1] == '"') || (s[0] == '\''
				&& s[1] == '\'')))
		return (0);
	if ((s[0] != '\'' && s[0] != '"') || s[len - 1] != s[0])
		return (0);
	return (1);
}

int	check_quotes_group(char *s, int *i)
{
	char	cur;
	int		cnt;

	cur = s[*i];
	cnt = 0;
	while (s[*i] && s[*i] == cur)
	{
		cnt++;
		(*i)++;
	}
	return (cnt % 2 == 0);
}

int	is_only_quotes(char *s)
{
	int	i;
	int	other;
	int	quote;
	int	len;

	i = 0;
	other = 0;
	quote = 0;
	len = ft_strlen(s);
	if (len == 2 && ((s[0] == '\"' && s[1] == '\"') || (s[0] == '\'' && s[1] == '\'')))
		return (1);
	while (s[i] && !ft_isspace(s[i]))
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = 1;
			if (!check_quotes_group(s, &i))
				return (0);
		}
		else
		{
			other = 1;
			i++;
		}
	}
	return (!other && quote);
}

int	is_only_backslashes_or_backtick(char *s)
{
	int		i;
	char	fc;

	if (!s || !*s)
		return (0);
	fc = s[0];
	if (fc != '\\' && fc != '`')
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] != fc)
			return (0);
		i++;
	}
	if (i % 2 == 0)
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 11:22:23 by yang              #+#    #+#             */
/*   Updated: 2022/05/05 23:52:11 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* check if env name is valid
** i. start with alpha or '_'
** ii. only consist of alpha, digit or '_'
*/

int	is_name(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	while (str[++i])
	{
		if (!is_env(str[i]))
			return (0);
	}
	return (1);
}

int	get_env_pos(char *str, int pos)
{
	int	i;
	int	quote;

	i = pos - 1;
	quote = 0;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] && (ft_isalpha(str[i + 1]) \
			|| str[i + 1] == '_' || str[i + 1] == '?'))
			return (i);
		else if (str[i] == '\'')
			quote = in_quote(str, i);
		if (quote > i)
			i = quote;
	}
	return (-1);
}

char	*get_prefix(char *str, int i)
{
	if (i > 0)
		return (ft_strndup(str, i));
	return (NULL);
}

char	*get_postfix(char *str, int *i)
{
	int		postfix_pos;
	int		j;

	postfix_pos = 0;
	j = *i;
	if (str[j + 1] == '?' && str[j + 2])
	{
		j += 2;
		postfix_pos = j;
	}
	else if (str[j + 1] != '?')
	{
		while (str[++j])
		{
			if (!is_env(str[j]))
			{
				postfix_pos = j;
				break ;
			}
		}
	}
	if (postfix_pos != 0)
		return (ft_strndup(str + j, ft_strlen(str) - j));
	return (NULL);
}

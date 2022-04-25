/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:25:35 by yang              #+#    #+#             */
/*   Updated: 2022/04/25 14:09:55 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "yeejin.h"

int	count(char *str, char c)
{
	int	total;
	int	i;

	i = -1;
	total = 1;
	while (str[++i])
	{
		if (str[i] == c || (str[i] == ' ' && c == ' ' && is_space(c)))
		{
			total++;
			while (i < (int)ft_strlen(str) - 2 && str[i + 1] == c)
				i++;
		}
		else if (str[i] == '"' || str[i] == '\'')
			i = in_quote(str, i);
		if (i == -1)
			return (-1);
	}
	return (total);
}

int	split_pos(char *str, int i, char c)
{
	while (i < (int)ft_strlen(str) - 2
		&& (str[i + 1] == c
			|| (str[i + 1] == c && c == ' ' && is_space(c))))
		i++;
	return (i);
}

/* separate user input into each cmd by c */
char	**ft_split_str(char *str, char c)
{
	char	**w_split;
	int		start_pos;
	int		i;
	int		j;

	w_split = malloc(sizeof(char *) * (count(str, c) + 1));
	if (!w_split)
		return (NULL);
	start_pos = 0;
	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] == c || (str[i] == ' ' && c == ' ' && is_space(c)))
		{
			w_split[++j] = ft_strndup(str + start_pos, i - start_pos);
			i = split_pos(str, i, c);
			start_pos = i + 1;
		}
		else if (str[i] == '"' || str[i] == '\'')
			i = in_quote(str, i);
	}
	w_split[++j] = ft_strndup(str + start_pos, i - start_pos);
	w_split[++j] = NULL;
	return (w_split);
}

void	free_malloc(char **array)
{
	int	i;

	i = -1;
	while (!array[++i])
		free(array[i]);
	free(array);
}

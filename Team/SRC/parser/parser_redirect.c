/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 10:59:12 by yang              #+#    #+#             */
/*   Updated: 2022/04/25 13:51:58 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "yeejin.h"

void	token_bef_operator(t_cmd *cmd, char **token, int pos, int i)
{
	char	dest[MAXCOM];
	t_list	*new;

	if (pos != 0)
	{
		ft_memset(dest, 0, MAXCOM);
		ft_strlcpy(dest, token[i], pos + 1);
		new = ft_lstnew(dest);
		set_token_type(new, i);
		ft_lstadd_back(&cmd->token, new);
	}
}

int	get_operator_pos(char **token, int pos)
{
	int		i;
	char	redirect;
	char	*str;

	i = 0;
	str = token[pos];
	while (str[i] && !is_operator(str[i]))
	{
		if (is_quote(str[i]))
			i = in_quote(str, i);
		i++;
	}
	redirect = str[i];
	if (i == (int)ft_strlen(str) - 1 && token[pos + 1] == NULL)
		return (-1);
	if (i < (int)ft_strlen(str) - 1 && is_operator(str[i + 1]))
	{
		if (str[i + 1] != redirect)
			return (-1);
	}
	return (i);
}

int	get_file_pos(char *str)
{
	int	i;

	i = 0;
	if (!is_operator(str[0]))
	{
		while (!is_operator(str[i]))
			i++;
	}
	while (is_operator(str[i]) && !is_space(str[i]))
		++i;
	return (i);
}

int	get_redirection_type(char *str)
{
	char	redirect;
	int		i;

	i = 0;
	redirect = str[i];
	if (ft_strlen(str) > 1 && is_operator(str[i + 1]))
	{
		if (str[i + 1] != redirect)
			return (-1);
		if (redirect == '>')
			return (GREATGREAT);
		return (LESSLESS);
	}
	else
	{
		if (redirect == '>')
			return (GREAT);
		return (LESS);
	}
}

int	set_token_redirection(t_cmd *cmd, char **token, int i)
{
	char	dest[MAXCOM];
	int		j;
	t_list	*new;

	while (token[i] && is_operator_in_str(token[i]))
	{
		j = get_operator_pos(token, i);
		if (j == -1)
			return (-1);
		token_bef_operator(cmd, token, j, i);
		ft_memset(dest, 0, MAXCOM);
		if (ft_strlen(token[i] + j) > 2)
			ft_strlcpy(dest, token[i] + get_file_pos(token[i]), \
			ft_strlen(token[i]) - get_file_pos(token[i]) + 1);
		else
			ft_strlcpy(dest, token[i + 1], ft_strlen(token[i + 1]) + 1);
		new = ft_lstnew(dest);
		new->type = get_redirection_type(token[i] + j);
		ft_lstadd_back(&cmd->token, new);
		if ((ft_strlen(token[i] + j) <= 2 && is_operator(token[i][j]))
			|| (ft_strlen(token[i] + j) == 2 && is_operator(token[i][j + 1])))
			i++;
		i++;
	}
	return (i);
}

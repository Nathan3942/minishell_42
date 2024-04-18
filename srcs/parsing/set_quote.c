/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 06:28:12 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/16 12:29:22 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	nb_cote(char **input, char c)
{
	int	i;

	i = 1;
	if (ft_strchr(ft_strchr(input[0], c) + 1, c))
		return (0);
	while (input[i] != NULL)
	{
		if (ft_strchr(input[i], c) != NULL)
			return (i);
		i++;
	}
	return (0);
}

static int	count_cote(char **input)
{
	int	i;
	int	z;
	int	cote_len;

	i = 0;
	z = 0;
	cote_len = 0;
	while (input[i] != NULL)
	{
		if (ft_strchr(input[i], '\'') != NULL)
			cote_len += nb_cote(input + i, '\'');
		if (ft_strchr(input[i], '\"') != NULL)
			cote_len += nb_cote(input + i, '\"');
		i++;
	}
	return (i - (cote_len));
}

static char	*entre_cote(char **input, char c)
{
	char	*res;
	int		i;

	i = 1;
	if (input[0] != NULL && ft_strchr(ft_strchr(input[0], c) + 1, c) != NULL)
		return (ft_strdup(input[0]));
	res = ft_strdup(input[0]);
	while (input[i] != NULL)
	{
		if (ft_strchr(input[i], c) != NULL)
			return (ft_strjoin_sp(res, input[i]));
		else
			res = ft_strjoin_sp(res, input[i]);
		i++;
	}
	res = ft_strdup(input[0]);
	return (res);
}

char	**set_cote(char **input)
{
	char	**result;
	int		i;
	int		z;

	i = count_cote(input);
	result = (char **)malloc ((i + 1) * sizeof(char *));
	i = 0;
	z = 0;
	while (input[i] != NULL)
	{
		if (strchr1x(input[i], '\'') == 1 && strchr1x(input[i], '\"') == 1)
			result[z++] = ft_strdup(input[i++]);
		if (ft_strchr2x(input, '\'', i) == 0)
		{
			result[z++] = entre_cote(input + i, '\'');
			i += nb_cote(input + i, '\'') + 1;
		}
		else if (ft_strchr2x(input, '\"', i) == 0)
		{
			result[z++] = entre_cote(input + i, '\"');
			i += nb_cote(input + i, '\"') + 1;
		}
	}
	result[z] = NULL;
	return (result);
}

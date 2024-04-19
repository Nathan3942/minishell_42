/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_para.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:08:28 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/19 15:06:37 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)
		|| c == 46 || c == 45 || c == 36)
		return (1);
	return (0);
}

static int	count_quote(char *str, int *i)
{
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'')
			(*i)++;
		return (1);
	}
	if (str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] != '\"')
			(*i)++;
		return (1);
	}
	return (0);
}

static int	count_red(char *str, int *i)
{
	int	len;

	len = 0;
	if (str[*i] == '<')
	{
		(*i)++;
		while (str[*i] == '<')
			(*i)++;
		return (1);
	}
	if (str[*i] == '>')
	{
		(*i)++;
		while (str[*i] == '>')
			(*i)++;
		return (1);
	}
	if (str[*i] == '|')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

static int	count_word(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 1)
		{
			len++;
			while (str[i] != '\0' && ft_isalnum(str[i]) == 1)
				i++;
		}
		len += count_quote(str, &i);
		len += count_red(str, &i);
		if (str[i] != '\0')
			i++;
	}
	return (len);
}

static int	red_len(char *str, int *i)
{
	int	len;

	len = 0;
	if (str[*i] == '<')
	{
		while (str[*i] == '<')
		{
			len++;
			(*i)++;
		}
		return (len);
	}
	else if (str[*i] == '>')
	{
		while (str[*i] == '>')
		{
			len++;
			(*i)++;
		}
		return (len);
	}
	return (len);
}

static int	quote_len(char *str, int *i)
{
	int	len;

	len = 0;
	if (str[*i] == '\'')
	{
		(*i)++;
		len++;
		while (str[*i] != '\0' && str[*i] != '\'')
		{
			(*i)++;
			len++;
		}
	}
	else if (str[*i] == '\"')
	{
		(*i)++;
		len++;
		while (str[*i] != '\0' && str[*i] != '\"')
		{
			(*i)++;
			len++;
		}
	}
	(*i)++;
	return (len + 1);
}

static int	count_len(char *str, int *i)
{
	int	len;

	len = 0;
	if (str[*i] == ' ')
		(*i)++;
	if (ft_isalnum(str[*i]) == 1)
	{
		while (str[*i] != '\0' && ft_isalnum(str[*i]) == 1)
		{
			(*i)++;
			len++;
		}
	}
	else if (str[*i] == '<' || str[*i] == '>')
		len = red_len(str, i);
	else if (str[*i] == '\'' || str[*i] == '\"')
		len = quote_len(str, i);
	else if (str[*i] == '|')
	{
		len = 1;
		(*i)++;
	}
	else
		(*i)++;
	return (len);
}

static char	*putword(char *word, char const *s, int i, int word_len)
{
	int	j;

	j = 0;
	while (word_len > 0)
	{
		word[j] = s[i - word_len];
		j++;
		word_len--;
	}
	word[j] = '\0';
	return (word);
}

static char	**split_arg(char *str, char **dest, int nb_wd)
{
	int	i;
	int	len;
	int	word;

	i = 0;
	word = 0;
	while (word < nb_wd)
	{
		len = count_len(str, &i);
		dest[word] = (char *)malloc ((len + 1) * sizeof(char));
		putword(dest[word++], str, i, len);
		len = 0;
	}
	dest[word] = NULL;
	return (dest);
}

char	**split_para(char *input)
{
	char	**dest;
	int		nb_wd;

	nb_wd = count_word(input);
	dest = (char **)malloc ((nb_wd + 1) * sizeof(char *));
	dest = split_arg(input, dest, nb_wd);
	return (dest);
}

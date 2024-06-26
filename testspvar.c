/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testspvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:54:28 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/17 16:42:37 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


static int	count_wd(char *str)
{
	int		i;
	int		len;
	bool	var;

	i = 0;
	len = 0;
	var = false;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && var == false)
		{
			len++;
			var = true;
		}
		if ((str[i] == ' ' || str[i] == '\"') && var == true)
		{
			len++;
			var = false;
		}
		i++;
	}
	return (++len);
}

int	count_len(char *str, int *i, bool *var)
{
	int	len;

	len = 0;
	while (str[*i] != '\0')
	{
		if (str[*i] == '$' && (*var) == false)
		{
			(*var) = true;
			break ;
		}
		if ((str[*i] == ' ' || str[*i] == '\"') && (*var) == true)
		{
			(*var) = false;
			break ;
		}
		(*i)++;
		len++;
	}
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

static char	**split_words(char *str, char **dest, int nb_wd)
{
	int		i;
	int		len;
	int		word;
	bool	var;

	i = 0;
	word = 0;
	var = false;
	while (word < nb_wd)
	{
		len = count_len(str, &i, &var);
		dest[word] = (char *)malloc ((len + 1) * sizeof(char));
		putword(dest[word++], str, i, len);
		len = 0;
	}
	dest[word] = NULL;
	return (dest);
}

char	**split_var(char *str)
{
	char	**dest;
	int		nb_wd;

	nb_wd = count_wd(str);
	dest = (char **)malloc ((nb_wd + 1) * sizeof(char *));
	if (!dest)
		return (0);
	dest = split_words(str, dest, nb_wd);
	return (dest);
}


int	main(void)
{
	char *str = "\"   ppp$USER   kaka$PWD\"";
	int i = 0;
	char **tab = split_var(str);
	while (tab[i] != NULL)
		printf("%s\n", tab[i++]);

	return (0);
}
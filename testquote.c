/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testquote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:39:54 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/16 12:07:51 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_strchr2x(char **str, char c, int i)
{
	int	count;
	int	z;

	count = 0;
	while (str[i] != NULL)
	{
		z = 0;
		while (str[i][z] != '\0')
		{
			if (str[i][z] == c)
				count++;
			if (count == 2)
				return (0);
			z++;
		}
		i++;
	}
	return (1);
}

static int	strchr2x(char *input, char c)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	while (input[i] != '\0')
	{
		if (input[i] == c)
			z++;
		if (z == 2)
			return (0);
		i++;
	}
	return (1);
}

static int	strchr1x(char *input, char c)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == c)
			return (0);
		i++;
	}
	return (1);
}

static int	nb_quote(char **input, char c)
{
	int	i;

	i = 1;
	if (strchr2x(input[0], c) == 0)
		return (0);
	while (input[i] != NULL)
	{
		if (strchr1x(input[i], c) == 0)
			return (i);
		i++;
	}
	return (0);
}

static int	count_quote(char **input)
{
	int	i;
	int	count_quote;

	i = 0;
	count_quote = 0;
	while (input[i] != NULL)
	{
		if (strchr1x(input[i], '\'') == 0)
			count_quote += nb_quote(input + i, '\'');
		if (strchr1x(input[i], '\"') == 0)
			count_quote += nb_quote(input + i, '\"');
		i++;
	}
	return (i - count_quote);
}

char	**set_quote(char **input)
{
	char	**res;
	int		i;
	int		z;

	i = count_quote(input);
	res = (char **)malloc ((i + 1) * sizeof(char *));
	i = 0;
	z = 0;
	while (input[i] != NULL)
	{
		if (ft_strchr2x(input, '\'', i) == 0)
		{
			res[z++] = entre_quote(input, '\'');
		}
	}
}

int main() {
    // Chaînes d'entrée
    char *input[] = {"'Bonjour", "papa'", "\"lalallla", "kaka\"",NULL};

    // Test de count_cote
    printf("Nombre de chaînes après suppression des guillemets : %d\n", count_quote(input));
	return(0);
}
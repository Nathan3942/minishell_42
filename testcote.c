/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testcote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 07:41:28 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/16 12:58:41 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1) + 1;
	dup = (char *) malloc(len * sizeof(*s1));
	i = 0;
	if (dup == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	strchr1x(char *input, char c)
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


char	*ft_strchr(const char *str, int c)
{
	while ((char)c != *str)
	{
		if (!*str)
			return (NULL);
		str++;
	}
	return ((char *)str);
}

char	*ft_strjoin_nl(char const *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (s2);
	new = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!new)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i++] = ' ';
	while (s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}

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
			return (ft_strjoin_nl(res, input[i]));
		else
			res = ft_strjoin_nl(res, input[i]);
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

int main() {
    // Chaînes d'entrée
    char *input[] = {"kuku" ,"'Bonjour", "kakaakkakaa","papa'", "cat", "\"lalallla", "kaka\"", "'leku", "camrer'",NULL};

    // Test de count_cote
    printf("Nombre de chaînes après suppression des guillemets : %d\n", count_cote(input));

    // Test de set_cote
    char **resultat = set_cote(input);
    printf("Résultat après suppression des guillemets :\n");
    for (int i = 0; resultat[i] != NULL; i++) {
        printf("%s\n", resultat[i]);
        free(resultat[i]); // Libérez la mémoire allouée pour chaque élément du résultat
    }
    free(resultat); // Libérez la mémoire allouée pour le résultat

    return 0;
}
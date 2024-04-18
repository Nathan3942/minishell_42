/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:26:07 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/16 12:28:50 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*ft_strjoin_sp(char const *s1, char *s2)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recherche_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 04:52:22 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/08 06:04:36 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*recherche_env(char *str, t_env **env)
{
	t_env	*head;
	int		i;

	head = *env;
	while (head != NULL && str != NULL)
	{
		i = 0;
		while (head->env_name[i] != '\0' && head->env_name[i] == str[i + 1])
			i++;
		if (ft_strlen(head->env_name) == i)
			return (head->env_value);
		head = head->next;
	}
	return ("");
}

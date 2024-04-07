/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 04:41:08 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/05 05:13:38 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_var(t_params **para, t_env **env)
{
	t_params	*head;
	t_env		*henv;
	int			i;
	char		*var;

	head = *para;
	henv = *env;
	while (head != NULL)
	{
		i = 0;
		while (head->com[i] != NULL)
		{
			if (head->com[i][0] == '$')
			{
				var = recherche_env(head->com[i] + 1, &henv);
				if (var != NULL)
				{
					free(head->com[i]);
					head->com[i] = ft_strdup(var);
				}
			}
			i++;
		}
		head = head->next;
	}
}
